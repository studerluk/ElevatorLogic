#!/usr/bin/python3


import time
from threading import Thread

(UP, DOWN) = range(2)


def getTerminalSize():
    import os
    env = os.environ
    def ioctl_GWINSZ(fd):
        try:
            import fcntl, termios, struct, os
            cr = struct.unpack('hh', fcntl.ioctl(fd, termios.TIOCGWINSZ,
        '1234'))
        except:
            return
        return cr
    cr = ioctl_GWINSZ(0) or ioctl_GWINSZ(1) or ioctl_GWINSZ(2)
    if not cr:
        try:
            fd = os.open(os.ctermid(), os.O_RDONLY)
            cr = ioctl_GWINSZ(fd)
            os.close(fd)
        except:
            pass
    if not cr:
        cr = (env.get('LINES', 25), env.get('COLUMNS', 80))

        ### Use get(key[, default]) instead of a try/catch
        #try:
        #    cr = (env['LINES'], env['COLUMNS'])
        #except:
        #    cr = (25, 80)
    return int(cr[1]), int(cr[0])


class Request():
	def __init__(self, level, direction):
		self.level = level
		self.direction = direction

	def __str__(self):
		heading = "error"
		if self.direction == UP: heading = "UP"
		elif self.direction == DOWN: heading = "DOWN"
		return "Level %d wants to go %s" % (self.level, heading)

class Queue():
	def __init__(self, elevators):
		self.requests = []
		self.elevators = elevators

	def __str__(self):
		tmp = [str(r) for r in self.requests]
		return "%d - %s" % (len(self.elevators), str(tmp))

	def addListener(self, elevators):
		self.elevators += elevators

	def matchElevator(self, request, elevator):
		if elevator.direction == request.direction:
			if elevator.direction == UP and elevator.pos <= request.level:
				return True
			elif elevator.direction == DOWN and elevator.pos >= request.level:
				return True
		if elevator.direction == None:
			return True
		return False

	def mainLoop(self):
		while True:
			tmpReqs = []
			for i in range(len(self.requests)):
				rMatched = False
				request = self.requests[i]
				for elevator in self.elevators:
					if self.matchElevator(request, elevator):
						rMatched = True
						elevator.add2DNL(request.level)
				if not rMatched: tmpReqs.append(self.requests[i])
			self.requests = tmpReqs
			print(str(self))
			time.sleep(1)
		
class Elevator():
	def __init__(self, name, pos=0, direction=None):
		self.name = name
		self.pos = pos
		self.dnl = []	# destination number list
		self.direction = direction

	def __str__(self):
		heading = "nowhere"
		if self.direction == UP: heading = "UP"
		elif self.direction == DOWN: heading = "DOWN"
		return self.name + " level %d heading %s with dnl %s" %(self.pos, heading, str(self.dnl))

	def add2DNL(self, level):
		self.dnl.append(level)
		if not self.direction:
			if self.pos < level:
				self.direction = UP
			elif self.pos > level:
				self.direction = DOWN
		if self.direction == UP:
			self.dnl = sorted(self.dnl)
		elif self.direction == DOWN:
			self.dnl = sorted(self.dnl)[::-1]

	def go(self):
		if self.direction == None:
			if self.pos < self.dnl[0]: self.direction = UP
			elif self.pos > self.dnl[0]: self.direction = DOWN

		if self.pos == self.dnl[0]: del self.dnl[0]
		elif self.direction == UP: self.pos += 1
		elif self.direction == DOWN: self.pos -= 1
		time.sleep(2)

	def mainLoop(self):
		print(self.name + " started")
		while(True):
			if len(self.dnl) > 0:
				self.go()
			else:
				self.direction = None
				time.sleep(1)
			print(self)

class Button():
	def __init__(self, queue, level):
		self.queue = queue
		self.level = level

	def up(self):
		req = Request(self.level, UP)
		self.queue.requests.append(req)

	def down(self):
		req = Request(self.level, DOWN)
		self.queue.requests.append(req)


print(getTerminalSize())

# --- populate ---
elevators = [Elevator("elevator 1: ", 6, DOWN)]
queue = Queue(elevators)

buttons = []
for i in range(0, 10):
	buttons.append(Button(queue, i))

# --- start queue ---
queueThread = Thread(target=queue.mainLoop)
queueThread.start()

# --- start elevators ---
elevatorThreads = []
for elevator in elevators:
	t = Thread(target=elevator.mainLoop)
	elevatorThreads.append(t)
	t.start()
buttons[7].up()

# --- start button simulation ---
seq =  [7, 0, 6, 7, 6, 1, 7, 5]
seq2 = [9, 2, 3, 8, 4, 0, 3, 2]
seq3 = [2, 3, 44, 21, 34, 65, 3, 1]

def buttonMainLoop(queue, level, direction, delay):
	time.sleep(delay)
	b = Button(queue, level)
	if level < direction: b.up()
	elif level > direction: b.down()

buttonThreads = []
for i in range(len(seq)):
	t = Thread(target=buttonMainLoop, args=(queue, seq[i], seq2[i], seq3[i]))
	buttonThreads.append(t)
	t.start()


