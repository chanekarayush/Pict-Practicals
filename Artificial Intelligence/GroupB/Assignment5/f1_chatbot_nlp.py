import streamlit as st
import json
import spacy

# Load the spaCy model
nlp = spacy.load("en_core_web_sm")

class F1ChatBot:
    def __init__(self, json_file_path="f1_questions.json"):
        self.json_file_path = json_file_path
        self.responses = self.load_responses()

    def load_responses(self):
        try:
            with open(self.json_file_path, 'r') as f:
                return json.load(f)
        except FileNotFoundError:
            return {}  # Return an empty dictionary if the file is not found
        except json.JSONDecodeError:
            return {}  # Return an empty dictionary if the json is incorrectly formatted.

    def preprocess(self, text):
        doc = nlp(text.lower())
        processed_tokens = [token.lemma_ for token in doc if token.is_alpha and not token.is_stop]
        return processed_tokens

    def get_response(self, question):
        processed_question = self.preprocess(question)

        for q, answers in self.responses.items():
            processed_stored_question = self.preprocess(q)
            if processed_question == processed_stored_question:
                if isinstance(answers, list):
                    return "\n".join(answers)
                else:
                    return answers

        return "Sorry, I don't have an answer for that question."

# Initialize the chatbot
bot = F1ChatBot()

# Set up Streamlit page
st.title("Formula One ChatBot")
st.write("Welcome to the F1 ChatBot! Ask me anything about Formula One.")

# User input
user_input = st.text_input("You: ", "")

# Display the bot's response when the user submits a question
if user_input:
    response = bot.get_response(user_input)
    st.write(f"Bot: {response}")
