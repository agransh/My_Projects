"""
File:       project1.py
Author:     Agransh Srivastava
Date:       10/28/2020
Section:    54
E-mail:     asrivas1@umbc.edu
Description: This project works like a game of monopoly, moving player around the umbc campus and allowing to buy property
"""
from sys import argv
from random import randint, seed
from board_methods import load_map, display_board


if len(argv) >= 2:
   seed(argv[1])

QUIT_STRING = False

def take_turn(player,move,board_file,go_money):
   position = player["position"]   #players position on the board
   position += int(move)         #changes position according to move
   position %= len(the_board)
   board=list(the_board)          #converts the board into a list
   player["position"]=position

   the_board[position] = the_board[position][0:6] + player["symbol"]
   print("Symbol of the player is", player["symbol"])  #sets the symbol for the player
   player["position"] = position         # sets position to players current position
   print (player["name"], "you have rolled a", move)      # shows how much the player has moved
   print (player["name"], " you have landed on ", board_file[position]["Place"]) #shows where the player has landed
   display_board(the_board) #displays the board after the roll with the players in it
   if int(player["money"])>=0:  #checks if players money is greater than 0 (for rent)
      if player == player1:
         if board_file[position]["Place"]in player2["properties"]:#if player1 owns that property
            player1["money"] -= int(places[board_file[position]]["Rent"])#reduce money from player 1
            player2["money"] += int(places[board_file[position]]["Rent"])#add money to player 2
            print(board_file[position]["Place"], "rent cost", places[board_file[[posiiton]][Rent]]) #tells the rent for that position

      elif player == player2:
         if board_file[position]["Place"]in player1["properties"]: #if player1 owns that property
            player2["money"] -= int(places[board_file[position]["Place"]]["Rent"]) #reduce money from player 2
            player1["money"] += int(places[board_file[position]["Place"]]["Rent"]) #add money to player 1
            print(board_file[position]["Place"], "rent cost", places[board_file[position]["Places"]]["Rent"])#tells the rent for that position
            print("\n")


      player["total_moves"] += move #adds to players total moves

      if player["total_moves"]>= (1*len(the_board)): # this code checks if players pass go and then add the go amount
         player["money"]+= go_money
         player["total_moves"] -= (1*len(the_board))

      choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
      while choice != "5": #choice runs while choice is not equal to 5
         if choice == "1":  #checks if player selects option 1

            if board_file[position]["Price"] == "-1":  # checks if the price of a property is -1
               print("This property cannot be bought")
               choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
            elif player["money"]>= int([board_file[position]["Price"]] and board_file[position]["Price"] not in player1["properties"] and board_file[position]["Place"]not in player2["properties"]): #this basically checks if the player can afford the property and if its not in the other players properties
               player["properties"].append(board_file[position]["Place"]) #adds the property to the players property
               player["money"]-= int(board_file[position]["Price"]) #subtracts money from the players balance
               places[board_file[position]["Place"]]["Owner"]= player["name"] #puts the property under players name
               print("You now own", board_file[position]["Place"]) #tells the player that they now own that property
               choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
            elif player["money"] < int(board_file[position]["Price"]): #checks if player has enough money to buy the property
               print("You dont have enough money to buy this property")
               choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
            elif board_file[position]["Place"] in player1["properties"] or board_file[position]["Place"] in player2["properties"]: #checks if the other player owns the property
               print("The other player already owns this property")
               choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
         elif choice == "2": #checks if option 2 is chosen
            info = input("What property do you want to get information for? ")
            if info in places: #checks for the properties information
               print(info)
               print("Price: ", places[info]["Price"])  #displays the price of the property
               print("Building: ", places[info]["Building"]) #displays how many buildings are on the property
               print("Owner: ", places[info]["Owner"]) #displays who is the owner of the property
               print("Rent: ", places[info]["Rent"] + " , ", places[info]["BuildingRent"], "With Building" ) #displays rent of place and the rent with the building
               choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
            else:
               print("That is not a location")
               choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
         elif choice == "3": #checks if choice 3 is chosen
            play_info= input("The players are: \n" + player1["name"] + "\n" + player2["name"]+ "\n which player do you want to know about? ") #displays the players and asks which player do you want the information for
            if play_info==player1["name"]: #checks if player1 is asked for
               print("Player name: ", player1["name"] ) #shows their name
               print("Player Symbol: ", player1["symbol"]) #shows their symbol
               print("Current Money: " , player1["money"]) #shows their current money
               print("Properties owned: ", player1["properties"], end= "\n" )  #shows how many properties are owned with names
               print("\n")
               choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
            elif play_info == player2["name"]:#checks if player1 is asked for
               print("Player Name: ", player2["name"])#shows their name
               print("Player Symbol: ",player2["symbol"])#shows their symbol
               print("Current Money: ", player2["money"])#shows their current money
               print("Properties owned: ", player2["properties"], end="\n") #shows how many properties are owned with names
               print("\n")
               choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
         elif choice == "4": #checks if choice 4 is chosen
            house = input("Which property do you want to build a house on? ")
            if house in places: #checks if house can be built on the given places in the map
               if house in player["properties"]: #checks if player owns the property
                  if player["money"] >= int(places[house]["BuildingCost"]): #checks if player has more money than the building cost
                     places[house]["Rent"] = places[House]["BuildingRent"] #if a building is built, the rent now is equal to the building rent
                     player["money"] -= int(places[house]["BuildingCost"])#subtract money from the players account
                     print("You have built a building on", house ) #tells player that they have built a house on that position
                     choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
                  else:
                     print("You dont have enough money")
                     choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
               else: #the property is not owned by the player
                  print("You need to buy the property first")
                  choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
            else:
               print("The property does not exist or it has a building on it already") #there is already a building on the property
               choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
         elif choice == "5": #checks if player chose option 5
            pass
         else:
            print("That is not a choice") #error checking
            choice = input("1)Buy_Property\n2)Get Property Info \n3) Get Player Info \n4)Build Building \n5)End Turn\n\n What do you want to do?  ")
   elif int(player["money"])<0: #lose condition
         pass
   
def play_game(starting_money, pass_go_money, board_file):
   nickname1=input("First player, what is your name? ")
   symbol1=input("First player, what symbol do you want your character you use? ").upper()
   while len(symbol1)> 1: #checks if the symbol is more than a character
      print("Symbol must be one character")
      symbol1=input("First player, what symbol do you want your character to use? ").upper()
   nickname2=input("Second player, what is your name? ")
   while nickname2 == nickname1: #checks for unique nicknames
      print("Player 1 has that name, please choose a different name")
      nickname2=input("Second Player, what is your name? ")
   symbol2= input("Second player, what character do you want to use? ").upper()
   while symbol2 == symbol1 or len(symbol2)>1:
      print("Symbols must be unique and only one character")
      symbol2=input("Second player,what symbol do you want to use? ").upper()
   player1["name"]= nickname1 #sets player1's nickname
   player2["name"]= nickname2 #sets player2's nickname
   player1["symbol"]=symbol1 #sets player1's symbol
   player2["symbol"]=symbol2 #sets player2's symbol
   player1["money"]=starting_money #sets player1's starting money
   player2["money"]=starting_money #sets player2's starting money

   broke = False # boolean condition
   while not broke: #this checks if the player has money(wish this was me)
      roll1 = randint(0, 6) #dice roll1
      roll2 = randint(0, 6) #dice roll2
      move = roll1+roll2 #sum of both rolls
      take_turn(player1,move,board_file, pass_go_money) #calls the take turn function for player1
      roll1 = randint(0, 6) #dice roll1
      roll2 = randint(0, 6)#dice roll2
      move = roll1+roll2 #sum of both rolls
      take_turn(player2, move, board_file, pass_go_money) #calls the take turn function for player2

      if player1["money"] < 0:  #checks if player 1 has gone bankrupt
         print(player1["name"], "has no money left")
         print(player2["name"], "is the winner")
         broke = True #sets boolean to true
      elif player2["money"]< 0: #checks if player 2 has gone bankrupt
         print(player2["name"], "is broke")
         print(player1["name"], "is the winner")
         broke = True #sets boolean to true
if __name__ == "__main__":
  the_board=[] # creates an empty list for the board
  places={}  #empty dictionary for places
  properties =  {  #puts places with their abbrevs. in properties
     "Place": {
        "Abbrev":"",
        }
     }
  file = load_map("proj1_board1.csv")
  for line in file: #accessing stuff from the csv file
     place = line.get("Place") #gets places from csv
     abbrev = line.get("Abbrev") #gets abbreviations from csv
     color = line.get("Color") #gets colors from csv
     position = line.get("Position") #gets positions from csv
     price = line.get("Price") #gets prices from csv
     rent =line.get("Rent") #gets rent from csv
     buildingRent = line.get("BuildingRent") #gets building rent from csv
     buildingCost = line.get("BuildingCost") #gets building cost from csv
     places[place] = { #stores all that in places
        "Abbrev" : abbrev,
        "Color" : color,
        "Position": position,
        "Price": price,
        "Rent" : rent,
        "BuildingRent" : buildingRent,
        "BuildingCost" : buildingCost,
        "Building" : "No",
        "Owner" : "Bank",
        }
     properties["Abbrev"] = abbrev #sets the abbreviations from the  properties and stores it into abbrev
     the_board.append(properties["Abbrev"].ljust(5) + "\n   ") #padding
players = { #players dictionary
   "player1": { #player 1 dictionary
      "name": "",
      "symbol": "",
      "money": 0,
      "position": 0,
      "properties":[],
      "total_moves" : 0,
   },
   "player2":{ #player 2 dictionary
      "name": "",
      "symbol": "",
      "money": 0,
      "position": 0,
      "properties":[],
      "total_moves" : 0,
   }
}
player1 = players["player1"] #sets player1 as player in the game
player2 = players["player2"] #sets player2 as a player in the game
play_game(1500, 200, file) #calls the play game function



    

   
        
        
