// Include the framework
#include "cppgram/cppgram.hpp"

using std::string;

using cppgram::Polling;
using cppgram::BasicBot;

using cppgram::types::Message;

using cppgram::commands::MessageCommand;

// Create the bot class
class MyBot : public BasicBot<MyBot> {
public:
  // Constructor
  MyBot(string &token) : BasicBot(token, "MyBot", this) {}

  // Copy constructor (needed)
  MyBot(const MyBot &b) : BasicBot(b, this) {}
};

// Function triggered on all messages that don't trigger a command
void processMessage(MyBot &bot, const Message &message) {
  // Answer with the text sent by the user
  bot.sendMessage("Hello folks!");
}

// Function called on /start messages
void startCommand(MyBot &bot, const Message &message) {
  // Answer
  bot.sendMessage("This is a start message");
}

int main() {
  // Declare your bot token
  string token = "token";
  auto bot = MyBot(token);

  // Set the pointer to the function triggered each message
  bot.processMessage = &processMessage;

  // The command that will trigger the bot
  string name = "start";

  // Create the command
  MessageCommand<MyBot> *command =
      new MessageCommand<MyBot>(name, &startCommand);

  // Activate it
  bot.commands().addCommand(command);

  // Create the polling with 8 threads
  auto poll = Polling<MyBot>(bot, 8);

  // then start it
  poll.run();
  return 0;
}
