"""
File:         royal_game_of_ur.py 
Author:       Agransh Srivastava
Date:         11/15/2020
Section:      54
E-mail:       asrivas1@umbc.edu
Description:  This code plays the Royal game of Ur
"""

from sys import argv
from random import choice
from board_square import BoardSquare, Urpieces


class RoyalGameOfUr:
    STARTING_piecesS = 7

    def __init__(self, board_file_name):
        self.board = None
        self.load_board(board_file_name)

    def load_board(self, board_file_name):
        """
        This function takes a file name and loads the map, creating BoardSquare objects in a grid.

        :param board_file_name: the board file name
        :return: sets the self.board object within the class
        """

        import json
        try:
            with open(board_file_name) as board_file:
                board_json = json.loads(board_file.read())
                self.num_piecess = self.STARTING_piecesS
                self.board = []
                for x, row in enumerate(board_json):
                    self.board.append([])
                    for y, square in enumerate(row):
                        self.board[x].append(BoardSquare(x, y, entrance=square['entrance'], _exit=square['exit'], rosette=square['rosette'], forbidden=square['forbidden']))

                for i in range(len(self.board)):
                    for j in range(len(self.board[i])):
                        if board_json[i][j]['next_white']:
                            x, y = board_json[i][j]['next_white']
                            self.board[i][j].next_white = self.board[x][y]
                        if board_json[i][j]['next_black']:
                            x, y = board_json[i][j]['next_black']
                            self.board[i][j].next_black = self.board[x][y]
        except OSError:
            print('The file was unable to be opened. ')

    def draw_block(self, output, i, j, square):
        """
        Helper function for the display_board method
        :param output: the 2d output list of strings
        :param i: grid position row = i
        :param j: grid position col = j
        :param square: square information, should be a BoardSquare object
        """
        MAX_X = 8
        MAX_Y = 5
        for y in range(MAX_Y):
            for x in range(MAX_X):
                if x == 0 or y == 0 or x == MAX_X - 1 or y == MAX_Y - 1:
                    output[MAX_Y * i + y][MAX_X * j + x] = '+'
                if square.rosette and (y, x) in [(1, 1), (1, MAX_X - 2), (MAX_Y - 2, 1), (MAX_Y - 2, MAX_X - 2)]:
                    output[MAX_Y * i + y][MAX_X * j + x] = '*'
                if square.pieces:
                    # print(square.pieces.symbol)
                    output[MAX_Y * i + 2][MAX_X * j + 3: MAX_X * j + 5] = square.pieces.symbol

    def display_board(self):
        """
        Draws the board contained in the self.board object

        """
        if self.board:
            output = [[' ' for _ in range(8 * len(self.board[i//5]))] for i in range(5 * len(self.board))]
            for i in range(len(self.board)):
                for j in range(len(self.board[i])):
                    if not self.board[i][j].forbidden:
                        self.draw_block(output, i, j, self.board[i][j])

            print('\n'.join(''.join(output[i]) for i in range(5 * len(self.board))))

    def roll_d4_dice(self, n=4):
        """
        Keep this function as is.  It ensures that we'll have the same runs with different random seeds for rolls.
        :param n: the number of tetrahedral d4 to roll, each with one dot on
        :return: the result of the four rolls.
        """
        dots = 0
        for _ in range(n):
            dots += choice([0, 1])
        return dots

    def player_dictionaries(self, player, color, pieces_list):
        """
        This function will define the players and the information with it
        """
        player = {} #player dictionary

        player_name = input("What is your name?") #player name
        player["Name"] = player_name   #stores the name
        player["Color"] = color    #stores their color
        print(player['Name'], "you will play as", color) #tells user their color
        player["[pieces]"] = pieces_list   #pieces list
        return player

    def white_pieces(self):
        """
        This function is for white pieces and its numbers (W1,W2,W3,etc)

        """
        white_pieces_list = [] #this is a list for the white pieces
        for i in range(6):
            user_piece = str(i) #assings numbers to pieces
            user_piece = "W" + user_piece #white piece with numbers
            white_pieces = Urpieces("White", user_piece)
        return white_pieces_list

    def black_pieces(self):
        """
         This function is for black pieces and its numbers (W1,W2,W3,etc)

        """
        black_pieces_list = [] #creates a list for the black pieces
        for i in range(6):
            user_piece = str(i) #assings numbers to pieces
            user_piece = "B" + user_piece
            black_pieces = Urpieces("Black", user_piece)
        return black_pieces_list

    def turns(self, player):
        """
        This function is for player turns
        """
        dice = self.roll_d4_dice(n=4) #this is for dice roll
        print(player["Name"], "you rolled", dice) #shows user the roll

        if dice > 0:  #this function checks if dice value is greater than 0
            user_move = False
            if player["Color"] == "White": #checks if its whites turn
                for i in self.white_pieces: #loop for movement for white pieces
                    if i.can_move(dice, self.white_pieces):
                        user_move = True
            else:
                for i in self.black_pieces: #loop for movement for black pieces
                    if i.can_move(dice, self.black_pieces):
                        user_move = True

            for i in range(len(player["pieces"])): #runs through the pieces
                if player["pieces"][i].position == None: #checks if any pieces are off the board
                    print(i + 1, player["pieces"][i].symbol, "currently off the board")
                else:
                    print(i + 1, player["pieces"][i].symbol, player["pieces"[i].postion]) 
            move_option = int(input("What move do you wish to make?")) #asks player what move the player wishes to make
            move_try = player["pieces"][move_option - 1].can_move 
            if move_try == True:#checks if the player can move that piece
                player["pieces"][move_option - 1].position = player["pieces"][move_option - 1].position
                for x in range(dice):
                    player["pieces"][move_option - 1].postion = player["pieces"][move_option - 1].position.next

        else:
            print("You can't move")

    def play_game(self):
        """
            Your job is to recode this function to play the game.
        """
        self.display_board() #display board function
        player1_dict = {} #player 1 dictionary
        player2_dict = {} #player 2 dictionary
        white_piece_on_board = [] #list for white piece on board
        black_piece_on_board = [] #list for black piece on board

        for i in range(7):
            user_piece = str(i)
            user_piece = "W" + user_piece
            black_pieces = Urpieces("White", user_piece) # this names and numbers the different pieces
            white_piece_on_board.append(i) #adds these pieces to the list

        for i in range(7):
            user_piece = str(i)
            user_piece = "B" + user_piece
            black_pieces = Urpieces("Black", user_piece) #this names and numbers the different pieces
            black_piece_on_board.append(i)#adds these pieces to the board

        player_1 = self.player_dictionaries(player1_dict, "White", white_piece_on_board)
        player_2 = self.player_dictionaries(player2_dict, "Black", black_piece_on_board)

        self.turns(player_1)
        self.turns(player_2)


if __name__ == '__main__':
    file_name = input('What is the file name of the board json? ') if len(argv) < 2 else argv[1]
    rgu = RoyalGameOfUr(file_name)
    rgu.play_game()
