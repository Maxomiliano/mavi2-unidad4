#include "Game.h"
#include "Ragdoll.h"
#include "Cannon.h"
#include "Box2DHelper.h"

// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
	// Inicialización de la ventana de renderizado
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom(); // Configuración del zoom de la cámara
	InitPhysics(); // Inicialización del mundo físico
	cannon = new Cannon(phyWorld, b2Vec2(10.0f, 90.0f));
}

// Método principal que maneja el bucle del juego
void Game::Loop()
{
	while (wnd->isOpen())
	{
		wnd->clear(clearColor); // Limpia la ventana con un color especificado
		DoEvents(); // Procesa los eventos del sistema
		UpdatePhysics(); // Actualiza la simulación física
		DrawGame(); // Dibuja el juego en la ventana
		wnd->display(); // Muestra la ventana renderizada
	}
}

// Actualiza la simulación física
void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8); // Avanza la simulación física
	phyWorld->ClearForces(); // Limpia las fuerzas aplicadas a los cuerpos
	phyWorld->DebugDraw(); // Dibuja el mundo físico (para depuración)
}

// Dibuja los elementos del juego en la ventana
void Game::DrawGame() {}

// Procesa los eventos del sistema
void Game::DoEvents()
{
	sf::Vector2i mousePixelPos = Mouse::getPosition(*wnd);
	sf::Vector2f mouseWorldPos = wnd->mapPixelToCoords(mousePixelPos);
	b2Vec2 mousePos(mouseWorldPos.x, mouseWorldPos.y);
	cannon->Rotate(mousePos);

	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close(); // Cierra la ventana
			break;
			
		case Event::MouseButtonPressed:
			b2Vec2 cannonPos = cannon->GetCannon()->GetPosition();
			b2Vec2 direction = mousePos - cannonPos;

			float distance = direction.Length();
			direction *= distance;

			float impulseMagnitude = 10;
			b2Vec2 impulse = impulseMagnitude * direction;

			Ragdoll* ragdoll = new Ragdoll(phyWorld, cannonPos);
			ragdoll->GetTorso()->ApplyLinearImpulseToCenter(impulse, true);


			break;
		}
	}
}

// Configura el área visible en la ventana de renderizado
void Game::SetZoom()
{
	View camara;
	camara.setSize(100.0f, 100.0f); // Tamaño del área visible
	camara.setCenter(50.0f, 50.0f); // Centra la vista en estas coordenadas
	wnd->setView(camara); // Asigna la vista a la ventana
}

// Crea los elementos estáticos del juego (suelo y paredes)
void Game::CreateWorldBoundaries()
{
	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	b2Body* topWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	topWallBody->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);
}

// Inicializa el mundo físico
void Game::InitPhysics()
{
	float density = 1.0f;
	float friction = 0.5f;
	float restitution = 0.5f;
	float cannonAngle = b2_pi / 1.5f;

	// Inicializa el mundo físico con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	// Inicializa el renderizador de depuración para el mundo físico
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX); // Configura el renderizado para que muestre todo
	phyWorld->SetDebugDraw(debugRender);

	CreateWorldBoundaries();
}

