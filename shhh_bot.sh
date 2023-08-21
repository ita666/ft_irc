#!/bin/bash

input=".botchatlogs"

HOST="$1"
PORT="$2"
PASS="$3"
NAME="Oh_My_God_What_A_Shhh_Bot"
CHAN="#AnimalFacts"

# Array of random facts
FACTS=(
"Elephants are the only animals that can't jump."
"The heart of a blue whale is so big, a human can swim through its arteries."
"The fingerprints of a koala are so similar to humans that they can taint crime scenes."
"Octopuses have three hearts."
"Starfish have no brain."
"Honeybees can recognize human faces."
"Cows have best friends."
"Squirrels plant thousands of new trees each year by merely forgetting where they put their acorns."
"A group of flamingos is called a 'flamboyance'."
"Seahorses are monogamous life mates and travel holding each other's tails."
"Some cats are allergic to humans."
"Ostriches can run faster than horses."
"Bats are the only mammals that can fly."
"There are over 20,000 species of bees."
"A group of frogs is called an army."
"Hummingbirds are the only birds that can fly backward."
"Cheetahs can't roar but can purr."
"Gorillas can catch human colds and other illnesses."
"Butterflies taste with their feet."
"Dolphins have names for one another."
"Frogs can't swallow with their eyes open."
"Only female mosquitoes bite."
"The world's smallest mammal is the bumblebee bat."
"Some worms can jump."
"Baby elephants suck their trunks for comfort, similar to how human babies suck their thumbs."
"Jellyfish are 95% water."
"The male seahorse carries and gives birth to babies."
"Penguins propose to their mates with a pebble."
"A crocodile can't stick its tongue out."
"Sea otters hold hands while sleeping to keep from drifting apart."
"Snails can sleep for up to three years."
"An ostrich's eye is bigger than its brain."
"Ants never sleep."
"The age of a tree can be determined by its rings."
"Elephants have been known to show empathy, even towards other species."
"Sharks have been around for over 400 million years."
"Owls turn their heads almost 360° but can't move their eyes."
"Only 5% of the ocean has been explored by humans."
"A group of crows is called a murder."
"A rhinoceros's horn is made of hair."
"A narwhal's tusk reveals its past living conditions."
"Dragonflies have been on earth for 300 million years."
"There are over 60,000 species of tree worldwide."
"The mimic octopus can impersonate up to 15 marine species."
"Reindeer eyes turn blue in the winter to help them see at lower light levels."
"Birds don't urinate."
"Axolotls can regenerate their body parts."
"Slow loris venom comes from a gland in the crook of its inner arm."
"The male discus fish looks after its young by secreting a nutritious fluid from its skin."
"The mantis shrimp has 16 color receptors, while humans have only three."
"Cats have whiskers on the backs of their front legs."
"Alligators will give manatees the right of way if they are swimming near each other."
"Seahorses have no stomach and must eat almost constantly to stay alive."
"The world's oldest known pet hamster was 4.5 years old."
"African elephants have bigger ears than Indian elephants."
)

if [ "$#" -ne 3 ]; then
    echo "Please launch the bot using: 'sh $0 <host> <port> <password>'"
    exit 1
fi

log_n_join()
{
    printf "PASS ${PASS}\r\n"
    printf "NICK ${NAME}\r\n"
    printf "USER ${NAME} * * :${NAME}\r\n"
    printf "JOIN ${CHAN}\r\n"
}

log_n_join > $input

# Function to send a random fact to the channel every 30 seconds
send_random_fact() {
    while true; do
        sleep 10
        random_fact=${FACTS[$RANDOM % ${#FACTS[@]}]}
        printf "PRIVMSG ${CHAN} :${random_fact}\r\n" >> $input
    done
}

# Start the random fact function in the background
send_random_fact &

trap "rm -f $input; exit 0" INT TERM EXIT
tail -f $input | nc $HOST $PORT | while read line; do
    if echo "$line" | grep -q "PRIVMSG ${CHAN}"; then
        printf "NOTICE ${CHAN} :Shhhhhhh\r\n" >> $input
    fi
done