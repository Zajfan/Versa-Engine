// VersaEngineAI/core/agent/ChatbotAgent.cpp

#include "ChatbotAgent.h"
#include <iostream>

namespace VersaEngine {
    namespace AI {

        ChatbotAgent::ChatbotAgent(const std::string& name, Logger* logger) :
            name_(name), logger_(logger) {
            nlu_ = std::make_unique<NLUComponent>();
            dialogue_ = std::make_unique<DialogueManager>();
            knowledge_ = std::make_unique<KnowledgeBase>();
            SetPersonality("friendly");
            SetLanguage("en-US");
        }

        ChatbotAgent::~ChatbotAgent() = default;

        void ChatbotAgent::ProcessUserInput(const std::string& text) {
            conversationHistory_.push_back("User: " + text);

            if (logger_) {
                logger_->Log("ChatbotAgent: Processing user input: " + text);
            }

            NLUResult result;
            try {
                result = nlu_->ProcessInput(text, languageCode_);
            }
            catch (const std::exception& e) {
                if (logger_) {
                    logger_->LogError("NLU Error: " + std::string(e.what()));
                }
                dialogue_->HandleNLUError();
                return;
            }

            try {
                dialogue_->UpdateState(result, knowledge_.get());
            }
            catch (const std::exception& e) {
                if (logger_) {
                    logger_->LogError("Dialogue Error: " + std::string(e.what()));
                }
                dialogue_->HandleDialogueError();
                return;
            }

            if (dialogue_->ShouldTriggerAction()) {
                std::string actionType = dialogue_->GetActionType();
                std::string parameters = dialogue_->GetActionParameters();
                if (actionCallback_) {
                    actionCallback_(actionType, parameters);
                }
            }
        }

        std::string ChatbotAgent::GenerateResponse() {
            std::string response = dialogue_->GenerateResponse(personality_, currentEmotion_);
            conversationHistory_.push_back("Chatbot: " + response);
            return response;
        }

        void ChatbotAgent::SetPersonality(const std::string& personalityType) {
            personality_ = personalityType;
            if (logger_) {
                logger_->Log("ChatbotAgent: Personality set to: " + personalityType);
            }
        }

        void ChatbotAgent::AddKnowledge(const std::string& question, const std::string& answer) {
            knowledge_->AddKnowledge(question, answer);
            if (logger_) {
                logger_->Log("ChatbotAgent: Added knowledge: " + question + " - " + answer);
            }
        }

        void ChatbotAgent::ClearConversationHistory() {
            conversationHistory_.clear();
            if (logger_) {
                logger_->Log("ChatbotAgent: Conversation history cleared.");
            }
        }

        void ChatbotAgent::SetActionCallback(ActionCallback callback) {
            actionCallback_ = callback;
            if (logger_) {
                logger_->Log("ChatbotAgent: Action callback set.");
            }
        }

        void ChatbotAgent::SetEmotion(const std::string& emotion) {
            currentEmotion_ = emotion;
            if (logger_) {
                logger_->Log("ChatbotAgent: Emotion set to: " + emotion);
            }
        }

        void ChatbotAgent::SetCurrentLocation(const std::string& location) {
            currentLocation_ = location;
            if (logger_) {
                logger_->Log("ChatbotAgent: Location set to: " + location);
            }
        }

        void ChatbotAgent::ObserveEvent(const std::string& eventType, const std::string& eventData) {
            if (logger_) {
                logger_->Log("ChatbotAgent: Observed event: " + eventType + " - " + eventData);
            }
            // Process the event and potentially update the chatbot's state or trigger actions
            // ...
        }

        void ChatbotAgent::SetLanguage(const std::string& languageCode) {
            languageCode_ = languageCode;
            if (logger_) {
                logger_->Log("ChatbotAgent: Language set to: " + languageCode);
            }
            // (Optional) Update NLU component and knowledge base for the new language
        }

        void ChatbotAgent::Speak(const std::string& text) {
            // 1. Use text-to-speech engine to synthesize speech from text
            // 2. (Optional) Log the spoken text
            if (logger_) {
                logger_->Log("ChatbotAgent: Speaking: " + text);
            }
        }

        std::string ChatbotAgent::Listen() {
            // 1. Use speech recognition engine to get user input from audio
            std::string recognizedText = ""; // Replace with actual recognized text
            if (logger_) {
                logger_->Log("ChatbotAgent: Heard: " + recognizedText);
            }
            return recognizedText;
        }

        void ChatbotAgent::SetUserData(const std::string& userId, const std::string& key, const std::string& value) {
            userData_[userId][key] = value;
            if (logger_) {
                logger_->Log("ChatbotAgent: Set user data for " + userId + ": " + key + " = " + value);
            }
        }

        std::string ChatbotAgent::GetUserData(const std::string& userId, const std::string& key) const {
            auto userIter = userData_.find(userId);
            if (userIter != userData_.end()) {
                auto dataIter = userIter->second.find(key);
                if (dataIter != userIter->second.end()) {
                    return dataIter->second;
                }
            }
            return "";
        }

    } // namespace AI
} // namespace VersaEngine