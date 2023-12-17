# Two-Player Tetris

Two-Player Tetris redesigns the classic Tetris game, introducing a competitive aspect for two players. Originally developed as a collaborative final project for CS246, this game has been extensively refined and upgraded for broader usage.

## UML Diagram: Adherence to SOLID Principles
The classes in this version of Tetris strictly adhere to SOLID principles, ensuring scalability and emphasizing high cohesion with low coupling. 
The UML diagram provided showcases the thoughtful design of the project, where abstract classes are employed alongside various design patterns to enable polymorphism and modular design.
![tetris_uml](https://github.com/tylyuu/two-player-tetris/assets/114101094/03bbc4eb-2756-48ff-8989-2c7b74528401)


## Design Patterns: Strengthening Game Architecture

Key design patterns are utilized to enhance the architecture of the game:

#### MVC(Model-View-Controller):
The MVC pattern is crucial in this game's design. The **Model** (Game) encapsulates core functionality and logic, the **View** (Text and Graphic Observers) manages UI logic and user display, and the **Controller** directs data flow and communication between the Model and View. This separation allows for multiple views, leading to more efficient code management and scalability.

#### Observer:
The Observer pattern ensures efficient data transactions in the game. The **Subject** (Board) interacts with its **Observers** (Text and Graphic Observers), automatically notifying them of any game state changes, facilitating loose coupling between interacting objects.

#### Factory: 
The Factory pattern allows the game board to create various block types without being tightly coupled to specific block classes, enhancing flexibility and ease of maintenance.

## Game Features
### Commands: Enhanced Control Options
The game supports both keyboard and cursor commands, with autofill for user convenience. A parse tree, coupled with a trie data structure, ensures efficient command parsing and scalability.

#### Supported keyboard commands: 
- `left`
- `right`
- `down`
- `clockwise`
- `counterclockwise`
- `drop`
- `restart`

#### Supported cursor commands:
| Command            | Key          | 
|--------------------|--------------|
| Move Left          | Left Arrow   | 
| Move Right         | Right Arrow  | 
| Rotate Clockwise   | Up Arrow     | 
| Rotate Counter-CW  | /            | 
| Drop               | Space        | 

## Display
The game offers both text and graphic displays, employing the SFML library for the graphical interface. This choice ensures a visually engaging and diverse gaming experience for all players.


