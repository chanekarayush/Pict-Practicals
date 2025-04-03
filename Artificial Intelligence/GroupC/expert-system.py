from experta import *

class EmployeePerformance(Fact):
    """Fact structure to store employee performance data."""
    pass

class PerformanceEvaluation(KnowledgeEngine):
    @Rule(EmployeePerformance(attendance=MATCH.att, tasks_completed=MATCH.tasks, teamwork=MATCH.team))
    def evaluate_performance(self, att, tasks, team):
        score = 0
        
        if att >= 90:
            score += 30
        elif att >= 75:
            score += 20
        else:
            score += 10
        
        if tasks >= 50:
            score += 40
        elif tasks >= 30:
            score += 25
        else:
            score += 15
        
        if team == "excellent":
            score += 30
        elif team == "good":
            score += 20
        else:
            score += 10
        
        if score >= 80:
            print("Performance Rating: Excellent")
        elif score >= 60:
            print("Performance Rating: Good")
        else:
            print("Performance Rating: Needs Improvement")

# Create and run the expert system
engine = PerformanceEvaluation()
engine.reset()
engine.declare(EmployeePerformance(attendance=85, tasks_completed=40, teamwork="good"))
engine.run()

