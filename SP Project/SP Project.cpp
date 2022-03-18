#include <SFML/Graphics.hpp>
#include<sfml/System.hpp>
#include<sfml/main.hpp>
#include<sfml/Window.hpp>
#include<sfml/Graphics.hpp>
#include<sfml/Audio.hpp>
#include<iostream>
#include<functional>
#include<random>
#include<algorithm>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<sstream>;
#define Max_main_menu 4 
using namespace sf;
using namespace std;
struct menu
{
  
    float width = 1080;
    float height = 720;
    int menu_select;   //to show element selector
    Font font;
    Text main_menu[Max_main_menu];
   
    void set_menu(float width, float height)
    {
        if (!font.loadFromFile("Evogria.otf"))
        {
        }

        //to move and selector
        main_menu[0].setFont(font);
        main_menu[0].setFillColor(sf::Color::Red);
        main_menu[0].setString("Play 1 Vs Computer");
        main_menu[0].setCharacterSize(45);
        main_menu[0].setPosition(Vector2f(400, 320));

        //to move and selector
        main_menu[1].setFont(font);
        main_menu[1].setFillColor(sf::Color::Red);
        main_menu[1].setString("Player 1 Vs Player 2");
        main_menu[1].setCharacterSize(45);
        main_menu[1].setPosition(Vector2f(400,395));

        //to move and selector
        main_menu[2].setFont(font);
        main_menu[2].setFillColor(sf::Color::Blue);
        main_menu[2].setString("Options");
        main_menu[2].setCharacterSize(45);
        main_menu[2].setPosition(Vector2f(400,455));

        //to move and selector
        main_menu[3].setFont(font);
        main_menu[3].setFillColor(sf::Color::Blue);
        main_menu[3].setString("Exit");
        main_menu[3].setCharacterSize(45);
        main_menu[3].setPosition(Vector2f(400,500));

        //to appear corser on first thing  0
        menu_select = 0;
    }
    //to return the word selected
    int mainmenu()
    {
        return menu_select;
    }
    //.......
    void draw(RenderWindow& window)   //& ::to reduce load on memory 
    {
        //to draw :play  and option  and  Exit
        for (int i = 0; i < Max_main_menu; i++)  //to pass on all   
        {
            window.draw(main_menu[i]);
        }
    }
    void moveup()
    {
        if (menu_select - 1 >= -1)  //check if not on the first item
        {
            main_menu[menu_select].setFillColor(Color::Blue);   //change the privous  item's color 
            menu_select--;   //move to the lower item

            if (menu_select == -1)  // move to upper item  
            {
                menu_select = 3;
            }
            main_menu[menu_select].setFillColor(Color::Red);   //change the new item's color
        }
    }
    void movedown()
    {
        if (menu_select + 1 <= Max_main_menu)  //check if not on the last item
        {
            main_menu[menu_select].setFillColor(Color::Blue);
            menu_select++;   //move to the lower item

            if (menu_select == 4)  //to reapet move  
            {
                menu_select = 0;
            }
            main_menu[menu_select].setFillColor(Color::Red);
        }
    }

};

int game_two_player(int num)
{
    int scorep2 = 0;
    int scorep1 = 0;
    int x;
    
    srand(time(NULL));
    x = 22;//rand() % 20+20;
    sf::Vector2f direction(x, x);
    float velocity = sqrt(direction.x * direction.x + direction.y * direction.y);

    sf::Clock clock;
    sf::Time time = clock.restart();
    const Time update = seconds(1.f / 30.f);


    sf::RenderWindow window(sf::VideoMode(1080, 720), "the game", sf::Style::Close | sf::Style::Resize);

    // sf::RectangleShape osos(sf::Vector2f(1080.0f, 720.0f));
    //osos.setFillColor(sf::Color::Green);

     //player 
    sf::RectangleShape player(sf::Vector2f(30.0f, 160.0f));
    sf::Texture playerTexture;
    playerTexture.loadFromFile("messi 1.jpg");
    player.setTexture(&playerTexture);
    player.setPosition(220.0f, 300.0f);

    //player2  
    sf::RectangleShape player2(sf::Vector2f(30.0f, 160.0f));
    sf::Texture player2Texture;
    player2Texture.loadFromFile("ronaldo 1.jpg");
    player2.setTexture(&player2Texture);
    player2.setPosition(800.0f, 320.0f);


    //the ground of studium
    sf::RectangleShape photo(sf::Vector2f(1080.0f, 720.0f));
    sf::Texture photoTexture;
    photoTexture.loadFromFile("2-7.jpg");
    photo.setTexture(&photoTexture);
    photo.setPosition(0.0, 0.0f);


    //the ball
    sf::CircleShape ball(20.0f);
    sf::Texture ballTexture;
    const float ball_redius = 12.0f;
    ballTexture.loadFromFile("ball44.png");
    ball.setTexture(&ballTexture);
    ball.setPosition(526.0f, 346.0f);


    //the goal at the right
    sf::RectangleShape goal1(sf::Vector2f(800.0f, 380.0f));
    sf::Texture goaltexture;
    goaltexture.loadFromFile("goall.png");
    goal1.setTexture(&goaltexture);
    goal1.setPosition(500.0f, 170.0f);


    //the goal at the left
    sf::RectangleShape goal2(sf::Vector2f(800.0f, 380.0f));
    sf::Texture goal2texture;
    goal2texture.loadFromFile("goal2.png");
    goal2.setTexture(&goal2texture);
    goal2.setPosition(-365.0f, 184.0f);


    //score 
    sf::Font font1;
    if (!font1.loadFromFile("Evogria.otf")) {
        cout << "eror\n";
    }
    sf::Text score;
    score.setFont(font1);
    score.setCharacterSize(50);
    score.setFillColor(Color::Black);
    score.setPosition(480.0f, 20.0f);
    score.setString(" 0  :  0 ");


    sf::Time second = sf::seconds(1.f);
    sf::Clock timers;




    sf::SoundBuffer ballhitsound;
    if (!ballhitsound.loadFromFile("ballsound.wav")) {
        std::cout << "eror";
    }
    sf::Sound ballsound;
    ballsound.setBuffer(ballhitsound);

    sf::SoundBuffer studiumsound;
    if (!studiumsound.loadFromFile("studium.wav")) {
        std::cout << "eror";
    }
    sf::Sound sstudiumsound;
    sstudiumsound.setBuffer(studiumsound);


    while (window.isOpen())
    {

        sf::Time increase = timers.getElapsedTime();

        cout << increase.asSeconds() << endl;



        sstudiumsound.play();
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            //sstudiumsound.play();

            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                printf("new widow width : %i new window wedth : %i \n", evnt.size.height, evnt.size.width);
                break;
            case sf::Event::TextEntered:
                if (evnt.text.unicode < 128)
                {
                    printf("%c", evnt.text.unicode);
                }
            }
        }
        //player2 moving 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            player2.move(-5.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            player2.move(5.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player2.move(0.0f, 5.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            player2.move(0.0f, -5.0f);
        }



        /*player moving*/

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            player.move(-5.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            player.move(5.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            player.move(0.0f, 5.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            player.move(0.0f, -5.0f);
        }

        /*player stop moving out side the frame*/
        if (player.getPosition().x < 103) {
            player.setPosition(103, player.getPosition().y);
        }
        if (player.getPosition().y < 15) {
            player.setPosition(player.getPosition().x, 15);
        }
        if (player.getPosition().x + player.getGlobalBounds().width > 540) {
            player.setPosition(540 - player.getGlobalBounds().width, player.getPosition().y);
        }

        if (player.getPosition().y + player.getGlobalBounds().height > 702) {
            player.setPosition(player.getPosition().x, 702 - player.getGlobalBounds().height);
        }

        /*player2 stop moving out side the frame */

        if (player2.getPosition().x < 0) {
            player2.setPosition(0, player2.getPosition().y);
        }
        if (player2.getPosition().y < 15) {
            player2.setPosition(player2.getPosition().x, 15);
        }
        if (player2.getPosition().x + player2.getGlobalBounds().width < 585) {
            player2.setPosition(585 - player2.getGlobalBounds().width, player2.getPosition().y);
        }
        if (player2.getPosition().x + player2.getGlobalBounds().width > 975) {
            player2.setPosition(975 - player2.getGlobalBounds().width, player2.getPosition().y);
        }

        if (player2.getPosition().y + player2.getGlobalBounds().height > 702) {
            player2.setPosition(player2.getPosition().x, 702 - player2.getGlobalBounds().height);
        }

        time = time + clock.restart();
        while (time >= update)
        {
            const auto pos = ball.getPosition();
            const auto time1 = update.asSeconds() * velocity;
            sf::Vector2f new_pos(pos.x + direction.x * time1, pos.y + direction.y * time1);

            //boll stop moving outside the frame
            if (new_pos.x - ball_redius < 88 && ball.getPosition().y < 170) {

                direction.x *= -1;
                new_pos.x = 88 + ball_redius;
            }

            else if (new_pos.x - ball_redius < 88 && ball.getPosition().y > 550) {

                direction.x *= -1;
                new_pos.x = 88 + ball_redius;
            }
            else if (new_pos.x - ball_redius < 0) {

                direction.x *= -1;
                new_pos.x = 350 + ball_redius;
                new_pos.y = 344 + ball_redius;
                velocity = 0;
                cout << endl;
                scorep1++;

            }

            else if (new_pos.y - ball_redius < 0) {
                direction.y *= -1;
                new_pos.y = 0 + ball_redius;

            }



            else if (new_pos.x + ball_redius >= 940 && ball.getPosition().y < 170) {
                direction.x *= -1;
                new_pos.x = 940 - ball_redius;

            }
            else if (new_pos.x + ball_redius >= 940 && ball.getPosition().y > 510) {
                direction.x *= -1;
                new_pos.x = 940 - ball_redius;

            }
            else if (new_pos.x + ball_redius >= 1080) {
                direction.x *= -1;
                velocity = 0;
                new_pos.x = 690 + ball_redius;
                new_pos.y = 344 + ball_redius;
                scorep2++;

            }

            else  if (new_pos.y + ball_redius >= 680) {
                direction.y *= -1;
                new_pos.y = 680 - ball_redius;

            }
            ball.setPosition(new_pos);
            time -= update;


            //ball move and block steks

            if (player.getGlobalBounds().intersects(ball.getGlobalBounds())) {
                player.setPosition(player.getPosition().x, player.getPosition().y);
                ballsound.play();
                sstudiumsound.play();
                velocity = 22;
                direction.x = direction.x * -1;

                new_pos.x = 100 + ball_redius;
                new_pos.y = 10 + ball_redius;
            }
            if (player2.getGlobalBounds().intersects(ball.getGlobalBounds())) {
                player2.setPosition(player2.getPosition().x, player2.getPosition().y);
                ballsound.play();
               
                velocity = 22;
                direction.y *= 1;
                direction.x *= -1;
                new_pos.x = 940 - ball_redius;

            }



        }
        //score increasing
        std::stringstream textscore;
        textscore << scorep1 << "  :  " << scorep2;
        score.setString(textscore.str());

       



        window.draw(photo);
        window.draw(ball);
        window.draw(player);
        window.draw(player2);
        window.draw(goal1);
        window.draw(goal2);
        window.draw(score);
       
        // window.draw(osos);
      
        window.display();
        window.display();
        window.display();
        window.display();
        window.display();
        window.display();
        window.display();
    }

        return num;
}


int main()
{
    sf::RectangleShape menuphoto(sf::Vector2f(1080.0f, 720.0f));
    sf::Texture menuphotoTexture;
    menuphotoTexture.loadFromFile("background.jpeg");
    menuphoto.setTexture(&menuphotoTexture);
    menuphoto.setPosition(0.0, 0.0f);


    int page_number;

    //to pass on all program 
    while (true)
    {
        RenderWindow window(VideoMode(1080, 720), "pong game");
        //user interface
        menu focus;
        focus.set_menu(1080, 720);
        //End

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                //user interface
                //to show which element pressed on  or  move up or down
                if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == Keyboard::Up)
                    {
                        focus.moveup();
                        break;
                    }
                    if (event.key.code == Keyboard::Down)
                    {
                        focus.movedown();
                        break;
                    }
                    if (event.key.code == Keyboard::Return)  //Return :: Enter
                    {
                        focus.mainmenu();
                        if (focus.mainmenu() == 0)
                        {
                            window.close();
                            page_number = 0;
                        }
                        if (focus.mainmenu() == 1)
                        {
                            window.close();
                            page_number = 1;
                        }
                        if (focus.mainmenu() == 2)
                        {
                            window.close();
                            page_number = 2;
                        }
                        if (focus.mainmenu() == 3)
                        {
                            window.close();
                            page_number = 3;
                        }
                    }
                }
                //End user interface
            }
            window.clear();
           
            window.draw(menuphoto);
            focus.draw(window);
            window.display();
            window.display();
        }
        if (page_number == 0)
        {
            // player1 VS computer

        }
        if (page_number == 1)
        {
            //player 1 VS player 2 
            game_two_player(1);
        }
        if (page_number == 2)
        {
            // option
        }
        if (page_number == 3)
        {
            break;
        }
    }

    return 0;
}