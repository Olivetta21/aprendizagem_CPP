#include <SFML/Graphics.hpp>
#include <random>
using namespace sf;

int main()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 255);
    short r, g, b, posy, dir = 5;
    r = g = b = posy = 0;

    RenderWindow janela(VideoMode(840, 480), "platform game");

    RectangleShape backGround(Vector2f(840, 480));
    backGround.setPosition(0, 0);
    backGround.setFillColor(Color(160, 160, 255, 255));

    RectangleShape chao(Vector2f(840, 20));
    chao.setPosition(0, 460);
    chao.setFillColor(Color(0, 255, 0, 255));

    CircleShape bola(15);
    bola.setPosition(10, 10);
    bola.setFillColor(Color(255, 0, 0, 255));


    RectangleShape seta_esquerda(Vector2f(20, 10));
    seta_esquerda.setPosition(780, 430);
    seta_esquerda.setFillColor(Color(0, 0, 255, 255));

    RectangleShape seta_direita(Vector2f(20, 10));
    seta_direita.setPosition(810, 430);
    seta_direita.setFillColor(Color(0, 0, 255, 255));

    Clock relogio;
    Clock tempPulando;

    float vel = 100;


    while (janela.isOpen())
    {
        Event iniciado;
        while (janela.pollEvent(iniciado))
        {
            if (iniciado.type == Event::Closed)
                janela.close();
        }

        if (iniciado.type == sf::Event::Resized) {
            // Atualize a posição e o tamanho do botão com base na nova janela
            sf::FloatRect visibleArea(0, 0, iniciado.size.width, iniciado.size.height);
            janela.setView(sf::View(visibleArea));

            //bola2.setPosition(iniciado.size.width / 2 - bola2.getSize().x / 2, iniciado.size.height / 2 - bola2.getSize().y / 2);
        }

        sf::Time deltaTempo = relogio.restart();

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            bola.setPosition(bola.getPosition().x - vel * deltaTempo.asSeconds(), bola.getPosition().y);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            bola.setPosition(bola.getPosition().x + vel * deltaTempo.asSeconds(), bola.getPosition().y);
        }



        if (iniciado.type == Event::KeyPressed) {
            tempPulando.restart();

            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                if (tempPulando.getElapsedTime() < sf::milliseconds(1000)) {
                    bola.setPosition(bola.getPosition().x, 50);
                }
            }
           
        }

        if (iniciado.type == Event::MouseButtonPressed) {
            Vector2i mousePos = Mouse::getPosition(janela);
            Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            if (seta_esquerda.getGlobalBounds().contains(mousePosFloat)) {
                seta_esquerda.setFillColor(Color(200, 200, 255, 255));
                bola.setPosition(bola.getPosition().x - vel * deltaTempo.asSeconds(), bola.getPosition().y);
            }
            else if (seta_direita.getGlobalBounds().contains(mousePosFloat)) {
                seta_direita.setFillColor(Color(200, 200, 255, 255));
                bola.setPosition(bola.getPosition().x + vel * deltaTempo.asSeconds(), bola.getPosition().y);
            }
        }
        else {
            seta_esquerda.setFillColor(Color(0, 0, 255, 255));
            seta_direita.setFillColor(Color(0, 0, 255, 255));
        }

        //if (bola.getPosition().y + bola.getRadius() * 2 > 460) bola.setPosition(bola.getPosition().x, 460 - bola.getRadius() * 2);
        if (chao.getGlobalBounds().contains(bola.getPosition().x, bola.getPosition().y+bola.getRadius()*2)) {}
        else bola.setPosition(bola.getPosition().x, bola.getPosition().y + 60 * deltaTempo.asSeconds());
        //else if(bola.getPosition().y + bola.getRadius() * 2 < 460) bola.setPosition(bola.getPosition().x, bola.getPosition().y + 60 * deltaTempo.asSeconds());

        janela.clear();
        janela.draw(backGround);
        janela.draw(chao);
        janela.draw(bola);
        janela.draw(seta_direita);
        janela.draw(seta_esquerda);
        janela.display();
        //sf::sleep(milliseconds(20));
    }

    return 0;
}