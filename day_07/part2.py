from collections import Counter
from itertools import chain


INPUT_S="""\
32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483
"""

# Map of symbol substitution
subs_map = {
    'A' : 'A',
    'K' : 'B',
    'Q' : 'C',
    'T' : 'D',
    '9' : 'E',
    '8' : 'F',
    '7' : 'G',
    '6' : 'H',
    '5' : 'I',
    '4' : 'K',
    '3' : 'L',
    '2' : 'M',
    'J' : 'N',
}

# Empty lists of hands for each given `type`
hands_five = []
hands_four = []
hands_full = []
hands_three = []
hands_double_pair = []
hands_pair = []
hands_zero = []

# Empty map of bids associated to each hand
hands2bids = {}

for line in INPUT_S.splitlines():
    hand, bid = line.split()

    # Map card values (A,...,J) to alphabetic values (A,...,N).
    # This is gonna allow us to easily sort same `type` hands,
    # such as three-of-a-kind_s, by the given rule of first-high-card,
    # second-high-card and so on
    hand = [subs_map[card] for card in hand]
    
    # Associate original bid to the "new" hand string
    hands2bids[''.join(hand)] = int(bid)

    # An extra steps is required here:
    # `J` acts as a Joker => we'll be converting it to the most common (excluding `J`) card 
    counter = Counter(*[hand])
    most_common_card = counter.most_common(1)[0][0]
    second_most_common_card = 'N'
    if len(counter.most_common()) > 1:
        second_most_common_card = counter.most_common(2)[1][0]
    
    if (most_common_card == 'N'):
        # most common is Joker -> convert Joker to second most common
        new_hand = [second_most_common_card if card == 'N' else card for card in hand]
    else:
        # most common is not Joker -> convert Joker to most common
        new_hand = [most_common_card if card == 'N' else card for card in hand]
    
    # Determine `type` of hand and populate type lists
    new_counter = Counter(*[new_hand])
    two_most = new_counter.most_common(2)

    if (two_most[0][1] == 5):
        hands_five.append(''.join(hand))
    elif (two_most[0][1] == 4):
        hands_four.append(''.join(hand))
    elif (two_most[0][1] == 3):
        if (two_most[1][1] == 2):
            hands_full.append(''.join(hand))
        else:
            hands_three.append(''.join(hand))
    elif (two_most[0][1] == 2):
        if (two_most[1][1] == 2):
            hands_double_pair.append(''.join(hand))
        else:
            hands_pair.append(''.join(hand))
    elif (two_most[0][1] == 1):
        hands_zero.append(''.join(hand))

# Given the relative order between different type hands
# is known, we can manually do a first macro-sorting from
# weakest (rank 0) to strongest (rank len(input)) hand
all_hands = [
    hands_zero,
    hands_pair,
    hands_double_pair,
    hands_three,
    hands_full,
    hands_four,
    hands_five,
]

# Now onto the micro-sorting of each hand type cluster
all_hands = [reversed(sorted(hand)) for hand in all_hands]

# Finally, create a single list out of all cluster.
# This list will contain hands sorted by weakest to strongest
all_hands = list(chain(*all_hands))

# Compute the total winnings
total_win = 0
for rank, hand in enumerate(all_hands):
    total_win += (rank + 1) * hands2bids[hand]

print(f"Total winnings: {total_win}")
