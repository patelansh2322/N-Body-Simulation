# PS3: N-Body Simulation

## Contact
Name: Ansh Patel
Section: 202
Time to Complete: ~18 Hours


## Description
Explain what the project does.

This project is a simulation of a universe containing celestial bodies, implemented using object-oriented programming principles. The universe consists of various planets, represented by instances of the CelestialBody class that are drawn on an SFML window. The program reads input data about the planets' positions, velocities, masses, and textures from a file and then displays the universe in a graphical window. Each planet is represented as a sprite using textures loaded from files. The simulation follows Newton's laws of motion and gravitational attraction, updating planetary positions and velocities over time. It also uses smart pointers to efficiently manage memory allocation and deallocation.

### Features
Describe what your major decisions were and why you did things that way.

I used object-oriented principles to organize the project. I made a Universe class to hold all the planets and their details and a CelestialBody class for each planet. To manage the planets, I used std::make_unique in the Universe class to control their lifetimes. This helps manage memory without needing to delete objects, lowering the chance of memory leaks. This was crucial because each planet is created from a file, and I wanted to clean up resources efficiently without manual memory management. I also used std::shared_ptr for the sf::Texture in the CelestialBody class. This ensures the texture is shared between the sprite and the celestial body without worrying about deleting it, as shared_ptr does that automatically. To make the program easier to use, I added special functions for inserting and extracting data in both the Universe and CelestialBody classes. These functions let you easily read planet data from a file and display the simulation state on the console, making the data easy to view, edit, and verify. Using std::istream and std::ostream operators also allows the program to work well with standard input and output operations, making it easier to use and maintain. Additionally, the simulation includes time-stepping functionality, allowing planets to move according to gravitational forces over discrete time intervals. The gravitational force is calculated using Newton’s law of universal gravitation, and velocity updates are performed accordingly.

### Memory
Describe how you managed the lifetimes of your objects, including if you used smart pointers.

I used std::make_unique in the Universe class to manage the lifetime of celestial bodies. This ensures that the CelestialBody objects are automatically destroyed when they go out of scope, preventing memory leaks. Additionally, in the CelestialBody class, I used std::shared_ptr for textures, ensuring that they are properly managed and not duplicated unnecessarily. Objects like CelestialBody are automatically managed by smart pointers. In the case of the Universe, the planets are stored in a vector of unique pointers (std::vector<std::unique_ptr<CelestialBody>>), ensuring that all celestial bodies are cleaned up correctly when the Universe is destroyed.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I had trouble printing the output in the required format, specifically using scientific notation while maintaining readability. However, with the help of online resources, I got it working. I also spent a significant amount of time understanding and implementing smart pointers, which was a valuable experience as it made memory management much easier and safer. Another challenge was handling the physics calculations for gravitational forces correctly. Ensuring numerical stability and avoiding division by zero errors required careful debugging. Additionally, implementing SFML for graphical representation was a learning experience, as positioning objects correctly within the window required proper scaling calculations. Overall, I learned a lot about memory management, object-oriented design, and physics-based simulations.

### Extra Credit
Anything special you did.  This is required to earn bonus points.
If you created your own universe file.  Describe it here and explain why it is interesting.

I added a background image that makes the experience much more immersive. The audio that plays in the background is supposedly how the universe sounds according to some sources. I thought it would add a nice touch to the whole experience. The SFML window also displays a timestamp that shows how many Earth days have elapsed in the given simulation. Additionally, I implemented a feature where users can customize the initial conditions of their universe by providing their own input files. This allows for experimenting with different planetary arrangements and observing how they evolve under gravitational forces.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

GIFs: Prof Dr.Daly
Text files: Prof Dr.Daly
Scientific notation: https://cplusplus.com/reference/ios/scientific/
Smart pointers: https://www.geeksforgeeks.org/smart-pointers-cpp/
Smart pointers: https://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one
Smart pointers: https://stackoverflow.com/questions/22571202/differences-between-stdmake-unique-and-stdunique-ptr-with-new
Background image: https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.space.com%2F26078-how-many-stars-are-there.html&psig=AOvVaw1q_nK8iQpsCTfraLHURCL4&ust=1740252602322000&source=images&cd=vfe&opi=89978449&ved=0CBcQjhxqFwoTCPDf0ajA1YsDFQAAAAAdAAAAABAE
Audio: https://freesound.org
Physics: Prof Dr.Daly