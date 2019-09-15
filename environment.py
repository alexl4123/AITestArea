import random


class Environment:
    def __init__(self, amountOfTiles,robotPosition):
        self.amountOfTiles = amountOfTiles
        self.tileList = []
        self.robotPosition = robotPosition

    def CreateTiles(self):
        for x in range(self.amountOfTiles):
            self.tileList.append(Tile(False))


class AgentSensors:
    def __init__(self,tileStatus,position,maxPosition):
        self.tileIsDirty = tileStatus
        self.position = position
        self.maxPosition = maxPosition

class AgentActors:
    def __init__(self,environment):
        self.environment = environment

    def RobotMovesLeft(self):
        if (self.environment.robotPosition > 0):
            self.environment.robotPosition -= 1

    def RobotMovesRight(self):
        if (self.environment.robotPosition < self.environment.amountOfTiles):
            self.environment.robotPosition += 1

    def RobotSucks(self):
            if self.environment.tileList[self.environment.robotPosition].isDirty == True:
                self.environment.tileList[self.environment.robotPosition].isDirty = False

class Tile:
    def __init__(self, isDirty):
        self.isDirty = isDirty


class Robot:
    def __init__(self,agentSensors, agentActors):
        self.agentSensors = agentSensors
        self.agentActors = agentActors

    def Clean(self):
        if(self.agentSensors.tileIsDirty == True):
            self.agentActors.RobotSucks()
        elif(self.agentSensors.position < self.agentSensors.maxPosition-1):
            self.agentActors.RobotMovesRight()

    def UpdateSensors(self,agentSensors):
        self.agentSensors = agentSensors
class AiTestArea:
    def __init__(self, environment):
        agentSensors = AgentSensors(environment.tileList[environment.robotPosition].isDirty,environment.robotPosition,environment.amountOfTiles)
        agentActors = AgentActors(environment)
        self.robot = Robot(agentSensors,agentActors)
        self.points = 0
        self.environment = environment


    def StartAi(self):
        for x in range(1000):
            #First let the robot clean
            self.robot.UpdateSensors(AgentSensors(environment.tileList[environment.robotPosition].isDirty,environment.robotPosition,environment.amountOfTiles))
            self.robot.Clean()
            #Then get the points of the robot and add them together
            for tile in self.environment.tileList:
                if(tile.isDirty == False):
                    self.points += int(1)






#Set the number of tiles, get the robot position and how many tiles are dirty
numberOfTiles = 100
robotPosition = random.randint(0, numberOfTiles - 1)

environment = Environment(numberOfTiles,robotPosition)
environment.CreateTiles()
environment.robotPosition = robotPosition
for x in range(numberOfTiles):
    environment.tileList[x].isDirty = bool(random.getrandbits(1))

aiTestArea = AiTestArea(environment)
aiTestArea.StartAi()


print(str(aiTestArea.points))

