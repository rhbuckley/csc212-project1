### How should we plan to store and write changes?

#### Option 1: Add a serialize & deserialize function to each class
    Pros: 
        - Would be easy to understand (from a high level)
        - Could be evenly divided in implementation

    Cons:
        - how would we serialize pointers? this feels way too hard

#### Option 2: Use UUIDs (Universally Unique Identifiers)
    Pros: 
        - ahhhhhhh
        - we can give each memory address a uuid
    Cons: 
        - hell


###### My Regrets
I thought that maintaining these relationships would be a good idea, as it 
shows that we put a lot of thought and planning into the code before we wrote
it but now I am sad. Time to get my notebook

### My Solution. 

Abolish the pointer relationships. They would certainly be good for a real world
program, but in a real world program we would be using a relational database. We 
are not here. 
