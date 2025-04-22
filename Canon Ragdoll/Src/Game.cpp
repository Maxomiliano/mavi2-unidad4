#include "Game.h"
#include "Ragdoll.h"
#include "Box2DHelper.h"

// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
	// Inicializaci�n de la ventana de renderizado
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom(); // Configuraci�n del zoom de la c�mara
	InitPhysics(); // Inicializaci�n del mundo f�sico
	ragdoll = new Ragdoll(phyWorld, b2Vec2(50.f, 70.f));
}

// M�todo principal que maneja el bucle del juego
void Game::Loop()
{
	while (wnd->isOpen())
	{
		wnd->clear(clearColor); // Limpia la ventana con un color especificado
		DoEvents(); // Procesa los eventos del sistema
		UpdatePhysics(); // Actualiza la simulaci�n f�sica
		DrawGame(); // Dibuja el juego en la ventana
		wnd->display(); // Muestra la ventana renderizada
	}
}

// Actualiza la simulaci�n f�sica
void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8); // Avanza la simulaci�n f�sica
	phyWorld->ClearForces(); // Limpia las fuerzas aplicadas a los cuerpos
	phyWorld->DebugDraw(); // Dibuja el mundo f�sico (para depuraci�n)
}

// Dibuja los elementos del juego en la ventana
void Game::DrawGame() {}

// Procesa los eventos del sistema
void Game::DoEvents()
{
	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close(); // Cierra la ventana
			break;
			/*
		case Event::MouseButtonPressed:
			float angle = cannonBody->GetAngle();
			b2Vec2 direction(std::cos(angle), std::sin(angle));

			float impulseMagnitude = 1000.0f;
			b2Vec2 impulse = impulseMagnitude * direction;

			//b2Vec2 cannonPosition = cannonBody->GetPosition();
			//b2Vec2 spawnPosition = cannonPosition + 9.0f * direction;

			//controlBody->SetTransform(spawnPosition, 0.0f);
			controlBody->SetTransform(b2Vec2(16, 80), 0);
			controlBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			controlBody->ApplyLinearImpulseToCenter(-impulse, true);

			break;
			*/
		}
	}

	ragdoll->GetTorso()->SetAwake(true); // Activa el cuerpo para que responda a fuerzas y colisiones
	if (Keyboard::isKeyPressed(Keyboard::Left))
		ragdoll->GetTorso()->ApplyForce(b2Vec2(-1500.0f, 0.0f), ragdoll->GetTorso()->GetWorldCenter(), true);
	if (Keyboard::isKeyPressed(Keyboard::Right))
		ragdoll->GetTorso()->ApplyForce(b2Vec2(1500.0f, 0.0f), ragdoll->GetTorso()->GetWorldCenter(), true);
	if (Keyboard::isKeyPressed(Keyboard::Down))
		ragdoll->GetTorso()->ApplyForce(b2Vec2(0, 500.0f), ragdoll->GetTorso()->GetWorldCenter(), true);
	if (Keyboard::isKeyPressed(Keyboard::Up))
		ragdoll->GetTorso()->ApplyForce(b2Vec2(0, -10500.0f), ragdoll->GetTorso()->GetWorldCenter(), true);
}

// Configura el �rea visible en la ventana de renderizado
void Game::SetZoom()
{
	View camara;
	camara.setSize(100.0f, 100.0f); // Tama�o del �rea visible
	camara.setCenter(50.0f, 50.0f); // Centra la vista en estas coordenadas
	wnd->setView(camara); // Asigna la vista a la ventana
}

// Crea los elementos est�ticos del juego (suelo y paredes)
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

// Inicializa el mundo f�sico
void Game::InitPhysics()
{
	float density = 1.0f;
	float friction = 0.5f;
	float restitution = 0.5f;

	// Inicializa el mundo f�sico con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	// Inicializa el renderizador de depuraci�n para el mundo f�sico
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX); // Configura el renderizado para que muestre todo
	phyWorld->SetDebugDraw(debugRender);

	CreateWorldBoundaries();
	cannonBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 25, 5);
	float angle = b2_pi / 1.5f;
	cannonBody->SetTransform(b2Vec2(10.0f, 90.0f), angle);
}

