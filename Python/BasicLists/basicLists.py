import random

#Lists can hold multiple data types at once
#Indexes start at 0
#Negative indices start from the end of the list (i.e. -1 is the last element)
#Access sub-List
    #-> list[4:] - list with everything from index 4 onward
    #-> list[4:8] - list with everything from index 4 to index 7
noun = []
noun_bodypart = ["arm", "leg", "hand", "foot", "toenail", "neck", "liver", "spleen", "forehead", "femur", "belly button", 
            "ear", "eyeball", "left nipple", "nose", "butt", "tongue", "pancreas", "funny bone", "jejunum", "colon",
            "right lung", "aorta", "kidney", "adrenal gland", "forearm", "collar bone", "shoulder", "kneecap"]
noun_animal = ["mink", "toad", "gazelle", "buffalo", "chicken", "hedgehog", "platypus", "cheetah", "warthog", "cat", "cow", "parrot", "otter",
               "hippopotamus", "koala", "horse", "moose", "jaguar", "tapir", "prairie dog", "weasel", "squirrel", "rabbit", "owl", "groundhog",
               "alpaca", "goat", "chipmunk", "chameleon", "gorilla", "capybara", "honey badger", "deer", "antelope", "orangutan", "mouse", "crocodile"]
noun_vegetable = ["bok choy", "broccoli", "cauliflower", "artichoke", "kale", "spinach", "asparagus", "celery", "fennel", "quinoa", "corn", "green beans",
                  "peas", "leek", "onion", "green onion", "zucchini", "eggplant", "chili pepper", "turnip", "carrot", "tomato", "bell pepper", "radish",
                  "cucumber", "arugula", "cabbage", "rhubarb", "rutabaga", "bitter melon", "durian", "papaya", "pumpkin", "nori", "potato", "yam"]
noun_clothing = ["shirt", "pants", "polo", "slacks", "jeans", "tank top", "shoes", "sandals", "skirt", "swimsuit", "jacket",
                 "scarf", "hat", "shorts", "jorts", "socks", "tie"]
noun_relative = ["brother", "sister", "step-brother", "step-sister", "cousin", "niece", "nephew", "aunt", "uncle", "great-aunt", "great-uncle",
                 "grandma", "grandpa", "second cousin", "cousin once removed", "third cousin", "second cousin twice removed", "fourth cousin",
                 "third cousin thrice removed"]
adjective = []
verb = []
verb_ing = []
verb_ed = []
adverb_ly = []

#Random element from 0 ... len(list)-1
length = len(noun_bodypart) #length of a list
bodypart = random.choice(noun_bodypart)

#extend - add one list to another
noun.extend(noun_bodypart)
#add new elements
noun.append("house") #add to the end
noun.insert(2, "house") #add to a specific index
noun.append(noun_bodypart[4:]) #add multiple elements
#remove elements
noun.remove("leg") #remove one element
noun.clear() #remove all elements
noun.pop() #removes the last element
#search elements
noun.index("spleen") #gives index of "spleen" if found, else error
noun.count("spleen") #gives nummber of times "spleen" occurs in the list
#sorting elements
noun.sort() #sorts in ascending order
noun.reverse() #reverses the current order of the elements
#cloning
nounCopy = noun.copy()