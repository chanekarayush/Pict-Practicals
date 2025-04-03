def diagnose_covid():
    print("COVID-19 Diagnosis Expert System")
    print("Answer the following questions with 'yes' or 'no'.")
    
    symptoms = {
        "fever": (input("Do you have a fever? ").strip().lower(), 3),
        "cough": (input("Do you have a cough? ").strip().lower(), 3),
        "breath": (input("Are you experiencing difficulty breathing? ").strip().lower(), 5),
        "fatigue": (input("Do you feel fatigued? ").strip().lower(), 3),
        "taste_smell": (input("Have you lost your sense of taste or smell? ").strip().lower(), 3),
        "headache": (input("Do you have a headache? ").strip().lower(), 1),
        "sore_throat": (input("Do you have a sore throat? ").strip().lower(), 1),
        "runny_nose": (input("Do you have a runny or stuffy nose? ").strip().lower(), 1),
        "body_aches": (input("Are you experiencing muscle or body aches? ").strip().lower(), 1),
        "chills": (input("Do you have chills or repeated shaking? ").strip().lower(), 1),
        "nausea": (input("Are you experiencing nausea or vomiting? ").strip().lower(), 1),
        "diarrhea": (input("Do you have diarrhea? ").strip().lower(), 1),
        "chest_pain": (input("Are you experiencing chest pain or pressure? ").strip().lower(), 5),
        "confusion": (input("Are you feeling confused or having difficulty concentrating? ").strip().lower(), 5),
        "skin_rash": (input("Do you have any skin rashes or discoloration of fingers/toes? ").strip().lower(), 1),
    }
    
    score = sum(weight for symptom, (response, weight) in symptoms.items() if response == "yes")
    
    if score >= 10:
        print("High likelihood of COVID-19. Please consult a doctor immediately.")
    elif 6 <= score < 10:
        print("Moderate risk of COVID-19. Consider getting tested.")
    elif 3 <= score < 6:
        print("Mild symptoms. Monitor your health and follow precautions.")
    else:
        print("Low risk of COVID-19. Stay safe and maintain hygiene.")

if __name__ == "__main__":
    diagnose_covid()

