// Include the framework
#include "cppgram/cppgram.hpp"

// Create the bot class
class MyBot : public cppgram::BasicBot<MyBot>
{
    public:
    // Constructor
    MyBot( string &token )
        : BasicBot( token, "MyBot", this )
    {
    }

    // Copy constructor (needed)
    MyBot( const MyBot &b )
        : BasicBot( b, this )
    {
    }
};

// Function triggered on all messages that don't trigger a command
void
processMessage( MyBot &bot, const cppgram::types::Message &message )
{
    // Answer with the text sent by the user
    bot.sendMessage( message.text.value() );
}

// Function called on /start messages
void
startCommand( MyBot &bot, const cppgram::types::Message &message )
{
    // Answer
    bot.sendMessage( "Hello folks!" );
}

int
main()
{
    // Declare your bot token
    std::string token = "token";
    auto        bot   = MyBot( token );

    // Set the pointer to the function triggered each message
    bot.processMessage = &processMessage;

    // The command that will trigger the bot
    std::string name = "start";

    // Create the command
    cppgram::commands::MessageCommand<MyBot> *command
            = new cppgram::commands::MessageCommand<MyBot>( name, &startCommand );

    // Activate it
    bot.commands().addCommand( command );

    // Create the polling with 8 threads
    auto poll = cppgram::Polling<MyBot>( bot, 8 );

    // then start it
    poll.run();
    return 0;
}
