
# PLAN:
# Instead of simulating the process with one ant having a 1/3 chance of going to each neighbouring node
# have a lot of ants and make 1/3 of them go to each neighbouring node at every step.
# With this method simulate the process for a lot of steps on a graph representing the ball to find the
# expected number of steps.
# Then simulate a similar process on a large graph representing the infinite floor for the number of steps
# that was the expectation on the ball, and see what fraction of ants have not finished by that point

POW = 3000
DIM = 100

class Ball:
    def __init__(self) -> None:
        self.adj = {
            0: {1, 9, 10},
            1: {0, 2, 15},
            2: {1, 3, 11},
            3: {2, 4, 16},
            4: {3, 5, 12},
            5: {4, 6, 17},
            6: {5, 7, 13},
            7: {6, 8, 18},
            8: {7, 9, 14},
            9: {0, 8, 19},
            10: {0, 11, 14},
            11: {2, 10, 12},
            12: {4, 11, 13},
            13: {6, 12, 14},
            14: {8, 10, 13},
            15: {1, 16, 19},
            16: {3, 15, 17},
            17: {5, 16, 18},
            18: {7, 17, 19},
            19: {9, 15, 18}
        }
        
        self.values = [0 for _ in range(20)]

class Grid:
    def __init__(self) -> None:
        self.adj = {}
        self.values = {}
        
        for i in range(DIM):
            node = DIM * i
            for j in range(DIM):
                self.values[node] = 0
                
                if j % 2 == 1:
                    self.addConnection(node, node - 1)
                
                # Connect every other column to neighbouring columns
                if i % 2 == 1:
                    if j != DIM - 1:
                        self.addConnection(node, node - DIM + 1)
                        if i != DIM - 1:
                            self.addConnection(node, node + DIM + 1)
                node += 1
                    
    
    def addConnection(self, num1, num2):
        if num1 not in self.adj: self.adj[num1] = []
        if num2 not in self.adj: self.adj[num2] = []
        self.adj[num1].append(num2)
        self.adj[num2].append(num1)
            
def findExpectationOnBall():
    steps = 2500
    done = {}
    ball = Ball()
    
    totalAnts = 3 ** POW
    ball.values[0] = totalAnts

    for step in range(steps):
        newBall = Ball()
        for loc in range(20):
            for neigh in ball.adj[loc]:
                newBall.values[neigh] += (ball.values[loc] // 3)
        
        for loc in range(20):
            ball.values[loc] = newBall.values[loc]
        
        done[step] = ball.values[0]
        ball.values[0] = 0
        
    totalDone = 0
    totalNumberOfSteps = 0
    for step in range(steps):
        totalNumberOfSteps += done[step] * (step + 1)
        totalDone += done[step]
        
    averageNumberOfStepsForFinishedAnts = totalNumberOfSteps / totalDone
    
    totalLeft = 0
    for i in range(20):
        totalLeft += ball.values[i]
    
    print("Fraction done", totalDone/totalAnts)
    print("Fraction left", totalLeft/totalAnts)
    print("Weighted average:", averageNumberOfStepsForFinishedAnts)
    
    return averageNumberOfStepsForFinishedAnts

 
def calcFractionLeftOnFloor(steps):
    grid = Grid()
    done = {}
    
    # start in the middle of the grid
    startLoc = (DIM ** 2 // 2) + DIM / 2
    
    totalAnts = 3 ** POW
    grid.values[startLoc] = totalAnts
    
    for step in range(steps):
        newGrid = Grid()
        
        for loc in range(DIM ** 2):
            for neigh in grid.adj[loc]:
                newGrid.values[neigh] += (grid.values[loc] // 3)

        for loc in range(DIM ** 2):
            grid.values[loc] = newGrid.values[loc]
        
        done[step] = grid.values[startLoc]
        grid.values[startLoc] = 0
        
    antsLeft = 0
    for i in range(DIM ** 2):
        antsLeft += grid.values[i]
        
    print("Exact answer:  ", antsLeft/totalAnts)
    print("Rounded answer:", round(antsLeft/totalAnts, 7))

steps = findExpectationOnBall()
print("--------")
calcFractionLeftOnFloor(int(steps))