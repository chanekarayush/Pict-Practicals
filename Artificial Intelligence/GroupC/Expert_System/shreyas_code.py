# Expert System on Employee Performance Evaluation
class Evaluation:
    def __init__(self) -> None:
        self.name = input("Enter name of employee: ")
        self.competencies = {
            "Communication" : [0,0,0],
            "Productivity" : [0,0,0],
            "Creativity" : [0,0,0],
            "Integrity" : [0,0,0],
            "Punctuality" : [0,0,0]
        }
        self.performance = {
            "Goal 1" : [0,0,0],
            "Goal 2" : [0,0,0],
            "Goal 3" : [0,0,0],
            "Goal 4" : [0,0,0],
            "Goal 5" : [0,0,0]
        }
    
    
    def printTable(self,hashMap : dict):
        if hashMap == self.competencies:
            print("Competency Goals")
            print("Competency\t\tRating\tWeightage\tWeighted Score")
            for key,value in self.competencies.items():
                print(f"{key}\t\t{value[0]}\t{value[1]}\t\t{value[2]}")
            print()
        else:
            print("Performance Goals")
            print("Goals\t\tRating\tWeightage\tWeighted Score")
            for key,value in self.performance.items():
                print(f"{key}\t\t{value[0]}\t{value[1]}\t\t{value[2]}")
            print()
    
    def input(self):
        print("Enter rating from 1-3")
        print("Weightage should be equal to 100")
        weightTotal = 0
        for key in self.competencies.keys():
            self.competencies[key][0] = int(input(f"Enter rating for {key}: "))
            self.competencies[key][1] = int(input(f"Enter weightage({100 - weightTotal} remaining): "))
            weightTotal += self.competencies[key][1]
        for key in self.performance.keys():
            self.performance[key][0] = int(input(f"Enter rating for {key}: "))
            self.performance[key][1] = int(input(f"Enter weightage({100 - weightTotal} remaining): "))
            weightTotal += self.performance[key][1]
    
    def calcScore(self):
        for key in self.competencies.keys():
            self.competencies[key][2] = self.competencies[key][0] * self.competencies[key][1] / 100
        for key in self.performance.keys():
            self.performance[key][2] = self.performance[key][0] * self.performance[key][1] / 100
    
    def calculate(self):
        self.input()
        print()
        self.calcScore()
        self.printTable(self.competencies)
        
        sumCompetancy = 0
        for key in self.competencies.keys():
            sumCompetancy += self.competencies[key][2]
        print(f"Sum of weighted scores-Comptency = {sumCompetancy}")
        print()
        sumPerformance = 0
        self.printTable(self.performance)
        for key in self.performance.keys():
            sumPerformance += self.performance[key][2]
        print(f"Sum of weighted scores-Performance = {sumPerformance}")
        print()
        total = (sumCompetancy + sumPerformance) 
        
        if total >= 2.7:
            total = "{:.2f}".format(total)
            print(f"Overall Rating of {self.name} (out of 3): {total}")
            print("Employee Exceeds expectations")
        elif total >= 1.7 and total < 2.7:
            total = "{:.2f}".format(total)
            print(f"Overall Rating of {self.name} (out of 3): {total}")
            print("Employee meets expectations")
        else:
            total = "{:.2f}".format(total)
            print(f"Overall Rating of {self.name} (out of 3): {total}")
            print("Employee fails expectations")


obj = Evaluation()
obj.calculate()
