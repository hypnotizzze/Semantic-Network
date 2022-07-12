# Semantic-Network
It is necessary to identify the concepts, entities, and situations of the subject area in accordance with the task, to describe the main types of relations in a given subject area using such binary relations for which it is possible to explicitly specify both the type of connection (generative, situational, causal, etc.) based on non-lexical properties and properties of simultaneity/heterogeneity, and to specify lexical meanings.
In Russian for a specific arc in a semantic network describing a given subject area.
The result should be presented as a graphical representation of a simple semantic network without attached procedures, indicating both the type of connection and its lexical meaning on the arcs.
The program should have the following features:
— Formation of a semantic network — adding, deleting, changing nodes and links between them.
— Automatic preservation of the semantic network in case of an emergency shutdown of the program and the computer.
— Restore the saved value after restarting.
— Displaying the entire semantic network in the form of a graph (possibly using a text or pseudographic representation).
— Search for the coherence of concepts: two concepts are introduced, it is checked whether they exist in the semantic network; if at least one does not exist, it is reported: "this concept does not exist.
" If both exist, an attempt is made to find all the ways connecting these concepts, both considering the possible direction of communication (properties of reflection, symmetry, transitivity) and without considering the possible direction of communication ("identification of potential connectivity").
It is necessary to consider the admissibility of the simultaneous presence of different types of connections between two nodes for all possible pairs.
The following connections are allowed between the two vertices of the semantic network: Gen-generative, Sit-situational, Neg-negative, Ins-instrumental, Com-commitative, Cog-correlative, Fin-finitive, Cais-causal, Pot-potensive.
A connection from one vertex to another of the same type can exist in a single instance.
When adding a connection that has the property of symmetry, feedback of the same type is created. Also, you cannot add a connection between two vertices with a transitivity property if a connection with such a property has already been added.
The property of symmetry has a negative and correlative relationship.
Situational, comitative and causal communication have the property of transitivity.
 
