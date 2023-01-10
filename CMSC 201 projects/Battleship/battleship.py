"""
File:    battleship.py
Author:  Agransh Srivastava
Date:    4/25/2021
Section: 12
E-mail:  asrivas1@umbc.edu
Description: This part of the program will be the logic of the overall game
"""

import board


class BattleshipGame:

    def __init__(self, size=10):
        """
        This is the constructor for the game
        :param size: the size of the board
        """
        #code for the each of the ships as well as their lengths
        self.player_boards = [board.Board(size), board.Board(size)]
        self.ships = {
            'Carrier': {
                'code': 3,
                'length': 5,
            },
            'Battleship': {
                'code': 4,
                'length': 4,
            },
            'Cruiser': {
                'code': 5,
                'length': 3,
            },
            'Submarine': {
                'code': 6,
                'length': 2,
            },
            'Destroyer': {
                'code': 7,
                'length': 1,
            }
        }
        self.values = {
            3: "Carrier",  #Carrier
            4: "Battleship",  #Battleship
            5: "Cruiser",  #Cruiser
            6: "Submarine",  #Submarine
            7: "Destroyer",  #Destroyer
        }
        self.game_loop = True

    def run_game(self):
        """
        This function runs the game
        """
        #This is where the ships are going to be placed
        print('Player 1, prepare to place your fleet.')
        self.place_ships(self.player_boards[0])
        print('Player 2, prepare to place your fleet.')
        self.place_ships(self.player_boards[1])

        #Here is where you play the game
        while self.game_loop:

            for turn in [0, 1]:
                #this turns the ships
                self.display_boards(turn)

                #Player 1's board (labled your board here so I can remember lol)
                your_board = self.player_boards[turn]

                #This allows the code to swap between 1 and 0
                not_turn = int(not bool(turn))

                #Player 2's board (aka enemy board)
                enemy_board = self.player_boards[not_turn]

                attack_loop = True
                while attack_loop:
                    #This part takes in the coords for attack
                    print('Enter x y coordinates to attack the enemy navy: ', end='')

                    input_ = input().split()

                    if len(input_) == 2:
                        x, y = map(int, input_)
                        shot = board.Coord(x, y)

                        response = self.check_shot(shot, enemy_board)

                        #This is if we miss the given shot
                        if response['code'] == 1:
                            print(response['message'])

                        #This part is if we make the given shot
                        if response['code'] != 1:
                            print(response['message'])
                            attack_loop = False
                            #Value to store is a useful variable which we will use later to check for sunk ship
                            value_to_store = enemy_board.dict_board[shot.to_string()]
                            #This registers the hit on the other board
                            enemy_board.register_shot(shot, response['result'])
                            if response['code'] == 2:
                                #This checks if a ship has sunk
                                response2 = self.check_sunk(value_to_store, enemy_board)
                                #if the ship is sunk, then we print a message
                                if response2['code'] == 1:
                                    print(response2['message'])
                    else:
                        print("[Invalid Input] Try Again")

                # Check if player has won
                if self.check_win(enemy_board):
                    #Ends the game
                    print("Player "+str((turn + 1))+ " has won.")
                    self.game_loop = False
                    turn += 1

    def check_win(self, target_board):
        """
        This function checks for who has won
        :param target_board:
        :return:
        """
        # Check if there is ship not sunk, if not then that player wins
        for pos in target_board.dict_board:
            if not target_board.dict_board[pos] in [0, 1, 2]:
                return False
        return True

    def check_shot(self, shot, target_board):
        """
        This function will check what happened when one player attacks and then displays the appropriate message
        :param shot: This is the shot inputted
        :param target_board:
        :return: the apppropriate message based upon what happened with the shot
        """
        if not target_board.dict_board.__contains__(shot.to_string()):
            return {
                'code': 1,
                'message': "[Error Shot Not Registered]Error your shot coordinates exceed the board!"
            }

        #Value is what will be hit on the other players board
        value = target_board.dict_board[shot.to_string()]
        #all the messages that are given in the game
        cases = {
            0: {
                'code': 0,
                'message': "[Shot Registered]You missed, you will be luckier next time!",
                'result': 1
            },
            1: {
                'code': 1,
                'message': "[Error Shot Not Registered]You have already hit this coordinate (And it was a MISS), try again by inserting another one!"
            },
            2: {
                'code': 1,
                'message': "[Shot Registered]You have already hit this coordinate (And it was a HIT), try again by inserting another one!"
            },
            3: {
                'code': 2,
                'message': "[Shot Registered]You hit the enemy Carrier!",
                'result': 2
            },
            4: {
                'code': 2,
                'message': "[Shot Registered]You hit the enemy Battleship!",
                'result': 2
            },
            5: {
                'code': 2,
                'message': "[Shot Registered]You hit the enemy Cruiser!",
                'result': 2
            },
            6: {
                'code': 2,
                'message': "[Shot Registered]You hit the enemy Submarine!",
                'result': 2
            },
            7: {
                'code': 0,
                'message': "[Shot Registered]You hit and SUNK the enemy Destroyer!",
                'result': 2
            }
        }

        return cases[value]

    def check_sunk(self, ship_value, target_board):
        """
        This function will check if the ship was sunk
        :param ship_value: this is for the value of the ship( all the ships info)
        :param target_board: enemy;s board
        :return:
        """
        for pos in target_board.dict_board:
            if ship_value == target_board.dict_board[pos]:
                return {'code': 0}

        return {'code': 1,
                'message': "[Sunk ship]You sunk the enemy %s!" % self.values[ship_value]}

    def place_ships(self, player_board):
        """
        This function places the ships on the board/s
        :param player_board: the player's board that the ship needs to be placed upon
        :return:
        """
        #Here are the input requests for the ships
        for ship_name in self.ships:
            placing_loop = True
            while placing_loop:
                player_board.get_board()
                print("Enter x y coordinates to place the " ,ship_name,":" ,end='')
                x, y = map(int, input().split())
                print("Enter Right or Down (r or d): ", end='')
                rotation = input()

                #This part calculates coordinates of where the ships are placed and it can also control them if they are free
                positions = board.Coord(x, y).extend(rotation, self.ships[ship_name]['length'])

                #The control positions of ships
                out_put = player_board.control(positions)

                #This checks if there is an error and keeps code in the cycle
                if out_put['code'] == 0:
                    print(out_put['message'])

                #If there is no error then we exit the cycle
                if out_put['code'] == 1:
                    print(out_put['message'])
                    player_board.place_ship(self.ships[ship_name]['code'], positions)
                    placing_loop = False

    def display_boards(self, turn):
        """
        This function will display both the players boards
        :param turn: this will turn the ship right or down
        :return:
        """
        left_board = self.player_boards[0].get_raw_board(bool(turn))
        right_board = self.player_boards[1].get_raw_board(not bool(turn))

        print(" ", *range(self.player_boards[0].size), sep="  ", end="\t\t\t")
        print(" ", *range(self.player_boards[1].size), sep="  ")

        for row_n in left_board:
            #This is player one's board's Row Header
            print(row_n + " ", end="")

            #This is player one's board's Rows
            for column_n in left_board[row_n]:
                print(left_board[row_n][column_n] + "|", end="")

            #This is player two's board's Row Header
            print("\t\t" + row_n + " ", end="")

            #This is player two's board's Rows
            for column_n in right_board[row_n]:
                print(right_board[row_n][column_n] + "|", end="")

            print()


if __name__ == '__main__':
    BattleshipGame().run_game()
