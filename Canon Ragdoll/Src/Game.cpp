#include "Game.h"
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
void Game::DrawGame(){}

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
		}
	}
	centerBody->SetAwake(true); // Activa el cuerpo para que responda a fuerzas y colisiones
	if (Keyboard::isKeyPressed(Keyboard::Left))
		centerBody->ApplyForce(b2Vec2(-1500.0f, 0.0f), centerBody->GetWorldCenter(), true);
	if (Keyboard::isKeyPressed(Keyboard::Right))
		centerBody->ApplyForce(b2Vec2(1500.0f, 0.0f), centerBody->GetWorldCenter(), true);
	if (Keyboard::isKeyPressed(Keyboard::Down))
		centerBody->ApplyForce(b2Vec2(0, 500.0f), centerBody->GetWorldCenter(), true);
	if (Keyboard::isKeyPressed(Keyboard::Up))
		centerBody->ApplyForce(b2Vec2(0, -10500.0f), centerBody->GetWorldCenter(), true);
}

// Configura el �rea visible en la ventana de renderizado
void Game::SetZoom()
{
	View camara;
	camara.setSize(100.0f, 100.0f); // Tama�o del �rea visible
	camara.setCenter(50.0f, 50.0f); // Centra la vista en estas coordenadas
	wnd->setView(camara); // Asigna la vista a la ventana
}

// Inicializa el mundo f�sico y los elementos est�ticos del juego
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

	// Crea los elementos est�ticos del juego (suelo y paredes)
	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	b2Body* topWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	topWallBody->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);


	b2Body* headBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 5, density, friction, restitution);
	headBody->SetTransform(b2Vec2(50.0f, 60.0f), 0.0f);

	centerBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 10, 20, density, friction, restitution);
	centerBody->SetTransform(b2Vec2(50.0f, 70.0f), 0.0f);

	b2Body* leftArmBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 2, 15, density, friction, restitution);
	leftArmBody->SetTransform(b2Vec2(45.0f, 70.0f), 0.0f);

	b2Body* rightArmBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 2, 15, density, friction, restitution);
	rightArmBody->SetTransform(b2Vec2(55.0f, 70.0f), 0.0f);

	b2Body* leftLegBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 2, 15, density, friction, restitution);
	leftLegBody->SetTransform(b2Vec2(48.0f, 88.5f), 0.0f);

	b2Body* rightLegBody = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 2, 15, density, friction, restitution);
	rightLegBody->SetTransform(b2Vec2(52.0f, 88.5f), 0.0f);

	
	
	//Cabeza y torso
	b2Vec2 headAnchor(50.0f, 62.0f);
	b2Vec2 centerAnchor(50.0f, 60.0f);
	b2DistanceJoint* headJoint = Box2DHelper::CreateDistanceJoint(phyWorld, headBody, headAnchor, centerBody, centerAnchor, 0, 0.5f, 0.2f);
	
	//Brazo izquierdo y torso
	b2Vec2 centerAnchorLA(46.0f, 62.0f);
	b2Vec2 leftArmAnchor(45.0f, 64.0f);
	b2DistanceJoint* leftArmJoint = Box2DHelper::CreateDistanceJoint(phyWorld, leftArmBody, leftArmAnchor , centerBody, centerAnchorLA, 1, 0.5f, 0.2f);

	//Brazo derecho y torso
	b2Vec2 centerAnchorRA(53.0f, 62.0f);
	b2Vec2 rightArmAnchor(55.0f, 64.0f);
	b2DistanceJoint* rightArmJoint = Box2DHelper::CreateDistanceJoint(phyWorld, rightArmBody, rightArmAnchor, centerBody, centerAnchorRA, 1, 0.8f, 0.1f);

	//Pierna izquierda y torso
	b2Vec2 centerAnchorLL(48.0f, 79.0f);
	b2Vec2 leftLegAnchor(48.0f, 82.5f);
	float leftLegLength = b2Distance(centerAnchorLL, leftLegAnchor) * 0.7f;
	b2DistanceJoint* leftLegJoint = Box2DHelper::CreateDistanceJoint(phyWorld, leftLegBody, leftLegAnchor, centerBody, centerAnchorLL, leftLegLength, 0.5f, 0.2f);

	//Pierna derecha y torso
	b2Vec2 centerAnchorRL(52.0f, 79.0f);
	b2Vec2 rightLegAnchor(52.0f, 82.5f);
	float rightLegLength = b2Distance(centerAnchorRL, rightLegAnchor) * 0.7f;
	b2DistanceJoint* rightLegJoint = Box2DHelper::CreateDistanceJoint(phyWorld, rightLegBody, rightLegAnchor, centerBody, centerAnchorRL, rightLegLength, 0.5f, 0.2f);
}

