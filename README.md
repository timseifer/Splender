# Splendor
Splendor is game with two people with the idea of collecting resources to get higher cost cards. Higher cost cards are worth more winning points and give you more resources. A more in depth explanation of the rules is listed below. This was the final project for comp 11 and I recieved all points for the project. Enjoy!


Setup:
run ./test splendor.data Y
or
run ./test splendor.data N

If this doesn't work compile with clang++

Rulebooke can be found here:
https://cdn.1j1ju.com/medias/7f/91/ba-splendor-rulebook.pdf

Terminal commands are here:
q - Quit the game.
p3 - Take 3 gems from the table, each of a different color. You specify the colors after the command,
e.g., p3 red white blue would put a red, white, and blue gem into your private collection.
p2 - Take 2 gems of the same color (only possible if there are 4 gems of that color on the table). You
specify the color after the command, e.g., p2 red would put 2 red gems into your private collection.
r - Reserve a visible card from the table. You specify the row by the first letter of its name (m - Mines, t - Transport, v - Vendors) and then the index of the card in that row (using 1-indexing), e.g, r m 4 would reserve the 4th card from the mine row. A gold gem is automatically put in your private collection if any gold gems are left on the board.
b - Purchase a visible card from the table. You use the same specification as above, e.g., b t 2. The gems necessary to purchase the card (including gold “wildcard” gems) are automatically spent, and any applicable discounts are applied automatically.
br - Purchase a reserved card. You specify the index of the card in your hand (using 1-indexing), e.g., br 2 would purchase the second reserved card in your hand. Gems are automatically spent and discounts are automatically applied as done in the previous command.

https://www.cs.tufts.edu/comp/11-2019f/schedule/hw11/hw11.pdf
