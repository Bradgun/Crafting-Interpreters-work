1.
expr → primary
expr → expr postfix

primary → IDENTIFIER
primary → NUMBER

postfix → "(" ")"
postfix → "(" arguments ")"
postfix → "." IDENTIFIER

arguments → expr
arguments → arguments "," expr

2.
class Animal a where
  speak :: a -> String
  legs  :: a -> Int

data Dog = Dog
data Cat = Cat

instance Animal Dog where
  speak Dog = "Woof"
  legs Dog  = 4

instance Animal Cat where
  speak Cat = "Meow"
  legs Cat  = 4