Skylimit - 2D Endless Jumper Game
Skylimit is a 2D endless jumper game developed using the Simple and Fast Multimedia Library (SFML) and following the Entities, Components, and Systems (ECS) architecture. The game revolves around a player navigating an endless vertical environment, jumping from platform to platform while avoiding obstacles and collecting power-ups. The architecture ensures a clean and modular design, making it easy to manage game entities and their behaviors.

This documentation provides detailed descriptions of the main files and functions within the Skylimit project, including key classes, their members, and methods. It serves as a guide for developers to understand the structure and functionality of the game, facilitating further development and maintenance.

Action.h
Summary
The Action class handles keyboard inputs in the game by storing the name of the action (e.g., "Move right") and whether the action is beginning or ending.

Members
std::string m_name: Stores the name of the action.
std::string m_type: Stores whether the action is beginning or ending.

Methods
Action(): Default constructor.
Action(const std::string& name, const std::string& type): Constructor that sets the name and type of the action.
const std::string& name() const: Method to get the name of the action.
const std::string& type() const: Method to get the type of the action.

Animation.h
Summary
The Animation class stores all the information related to animations in the game.

Members
sf::Sprite m_sprite: A rectangle with an associated texture.
size_t m_frameCount: Counts the number of frames in a sprite.
size_t m_currentFrame: The current animation frame.
size_t m_speed: The speed at which the frames refresh.
Vec2 m_size: The size of the sprite.
std::string m_name: The name of the animation.

Methods
Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed): Constructor for moving entities.
Animation(const std::string& name, const sf::Texture& t): Constructor for static entities.
Animation(): Default constructor.
void update(): Advances to the next animation frame according to the speed.
std::string& getName(): Method to get the name of the animation.
Vec2& getSize(): Method to get the size of the animation.
sf::Sprite& getSprite(): Method to get the sprite of the animation.

Assets.h
Summary
The Assets class stores all game assets, including fonts, backgrounds, textures, sounds, animations, etc.

Members
AnimationsMap m_animations
Backgrounds m_backgrounds
Textures m_textures
SoundBuffers m_soundBuffers
Fonts m_fonts
Musics m_musics
Sounds m_sounds

Methods
~Assets(): Destructor.
void addTexture(const std::string& name, const std::string& path).
void addSoundBuffer(const std::string& name, const std::string& path).
void addFont(const std::string& name, const std::string& path).
void addAnimation(const std::string& name, const Animation & animation).
void addBackground(const int name, const int index2, const sf::Texture&).
void addMusic(const std::string& name, const std::string& path).
sf::Texture& getTexture(const std::string& name).
sf::SoundBuffer& getSoundBuffer(const std::string& name).
sf::Sound& getSound(const std::string& name).
sf::Font& getFont(const std::string& name).
Animation& getAnimation(const std::string& name).
Background& getBackground(const int name).
sf::Music* getMusic(const std::string& name).
void loadFromFile(const std::string& path): Retrieves and stores all assets from a file.

Background.h
Summary
The Background class defines the backgrounds and their different layers.

Members
std::vector<sf::Sprite> m_layers: Vector that stores the background sprites.
int m_length: Number of layers in a background.

Methods
void addLayer(const sf::Texture& t): Adds a layer to form the background.
Background(): Default constructor.
size_t getLength(): Gets the number of layers.
std::vector<sf::Sprite>& getLayers(): Gets the layer vector.

Components.h
Summary
Defines various components for entities in the game.

Classes
Component: Base class with a boolean has to determine existence.
CTransform: Handles transformations and translations.
Vec2 pos: Position vector.
Vec2 prevPos: Previous position vector.
Vec2 velocity: Velocity vector.

CInput: Handles player input.
bool up, bool right, bool left, bool canJump.

CBoundingBox: Defines the hitbox.
Vec2 size, Vec2 halfSize.

CAnimation: Defines entity animation.
Animation animation, bool repeat.

CGravity: Defines gravity for entities.
float gravity.

CState: Defines the state of the player (e.g., jumping, moving).
std::string state.

CKill: Indicates if an entity can kill the player.

CMove: Indicates if an entity can move.

Entity.h
Summary
Defines an entity and its components.

Members

ComponentTuple m_components: Tuple of all components.
std::string m_tag: Tag associated with the entity (e.g., enemy, tile).
bool m_active: Indicates if the entity is active.
size_t m_id: Unique identifier for the entity.
Methods
Entity(const size_t& id, const std::string& tag): Private constructor.
size_t id(): Returns the entity's ID.
bool isActive(): Returns if the entity is active.
const std::string& tag(): Returns the entity's tag.
void destroy(): Destroys the entity.
template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs): Adds a component to the entity.
template <class T> bool hasComponent(): Checks if the entity has a specific component.
template <typename T> T& getComponent(): Gets a specific component.
template <class T> void removeComponent(): Removes a specific component.

EntityManager.h
Summary
Handles all entities in the game.

Members
EntityVec m_entities: Vector of entities.
EntityVec m_toAdd: Vector of entities to be added next frame.
EntityMap m_entityMap: Map of entities by tag.
size_t m_totalEntities: Total number of entities.

Methods
void removeDeadEntities(EntityVec& vec): Removes dead entities.
void init(): Initializes the entity manager.
void update(): Updates the entity manager, adding and removing entities.
std::shared_ptr<Entity> addEntity(const std::string& tag): Adds a new entity.
EntityVec& getEntities(): Returns all entities.
EntityVec& getEntities(const std::string& tag): Returns entities by tag.

GameEngine.h
Summary
The main game engine class.

Members
sf::RenderWindow m_window: Game window.
Assets m_assets: Game assets.
std::string m_currentScene: Current scene identifier.
SceneMap m_sceneMap: Map of scenes.
size_t m_coins, float m_volume, size_t m_highestScore: Game configurations.
bool m_music, bool m_wasd: Game settings.
bool m_running: Indicates if the game is running.
sf::Music* m_currentMusic: Pointer to current music track.

Methods
void init(const std::string& path): Loads assets.
void update(): Checks user input and updates the scene.
void sUserInput(): Registers and checks user input.
std::shared_ptr<Scene> currentScene(): Returns the current scene.
void changeScene(const std::string&, std::shared_ptr<Scene> scene, bool endCurrentScene): Changes the scene.
void run(): Main game loop.
void quit(): Quits the game.
Assets& getAssets(): Returns a reference to the assets.
sf::RenderWindow& window(): Returns a reference to the window.
bool isRunning(): Returns if the game is running.
size_t getCoins(), float getVolume(), size_t getHighestScore(): Gets configurations.
bool getMusic(), bool getWASD(): Gets settings.
void setCoins(size_t coins), void setVolume(float volume), void setHighestScore(size_t highestScore): Sets configurations.
void setMusic(bool music), void setWASD(bool wasd): Sets settings.
void startMusic(const std::string& musicName): Starts playing music.
void stopMusic(): Stops the music.
void setMusicState(bool musicOn): Sets music state.
void switchToMusic(const std::string& musicName): Switches to a different music track.

Physics.h
Summary
Handles collision detection.

Methods
Vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b): Calculates overlap between two rectangles.
Vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b): Calculates overlap from the previous frame.

Scene.h
Summary
Defines a game scene.

Members
GameEngine& m_game: Reference to the main game engine.
EntityManager m_entityManager: Manages entities.
size_t m_currentFrame: Frame counter.
bool m_paused: Indicates if the scene is paused.

Methods
Scene(GameEngine& gameEngine): Constructor.
EntityManager& getEntityManager(): Returns the entity manager.
GameEngine& game(): Returns a reference to the game engine.
bool isPaused() const: Returns if the scene is paused.
void setPaused(bool paused): Sets the paused state.
size_t currentFrame() const: Returns the current frame.
void simulate(const size_t frames): Simulates a number of frames.
void doAction(Action& action): Defines action behavior.
virtual void update(): Updates the scene.
virtual void onEnd(): Called when the scene ends.

Vec2.h
Summary
Defines a 2D vector.

Members
float x, float y: Coordinates.

Methods
Vec2(): Default constructor.
Vec2(float xin, float yin): Constructor.
Vec2 operator + (const Vec2& v) const, Vec2 operator - (const Vec2& v) const: Overloaded operators.
Vec2 operator / (float val) const, Vec2 operator * (float val) const: Overloaded operators.
void operator += (const Vec2& v), void operator -= (const Vec2& v): Overloaded operators.
void operator *= (float val), void operator /= (float val): Overloaded operators.
bool operator == (const Vec2& v) const, bool operator != (const Vec2& v) const: Overloaded operators.
float dist(const Vec2& v) const: Distance to another vector.
float length() const: Vector length.
Vec2 normalized() const: Normalizes the vector.
void normalize(): Normalizes the vector.
Vec2 abs() const: Absolute value of the vector.
