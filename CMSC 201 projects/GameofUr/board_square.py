"""
File:         board_square.py
Author:       Agransh Srivastava
Date:         11/15/2020
Section:      54
E-mail:       asrivas1@umbc.edu
Description:  This code is the board square file for Royal game of Ur
"""

class UrPiece:
    def __init__(self, color, symbol):
        self.color = color
        self.position = None
        self.complete = False
        self.symbol = symbol

    def can_move(self, total_moves, start_sqauare, color):
        """
        this function checks if the piece can move to a certain tile
        """
    movable = True

    if total_moves == 0: #Checks if total moves are 0
        movable = False
        return movable

    if self.complete:
        movable = False
        return movable

    if not self.position: #checks if piece is not at the starting square
        current_position = start_square
        total_moves -= 1

    else:
        current_position = self.position #sets current position to self position

    for i in range(total_moves): #runs for total moves

        if movable and current_position.exit and i + 1 == total_moves: #checks if moveable and current position are equal to total moves
            current_position.piece = None #sets current position of the piece to none
            self.complete = True #self complete becomes true

        elif movable and current_position.exit and i + 1 < total_moves: #checks if the piece ismoveable and current_position are less than total moves
            movable = False #the piece is not moveable
            return movable

        elif movable and self.color == WHITE: #if piece  is movealble and the color of the piece is white
            current_position.position = current_position.next_white #current position becomes next white

        elif movable:# else if piece is moveable at all
            current_position.position = current_position.next_black #else set that position to next black

    if movable and current_position.piece == None: #checks if the piece is moveable but current position is none
        print("There is nothing on this square")
        return movable

    elif movable and current_position != None : #checks if the piece is moveable but the position is none
        print("There is a player piece on this square")

        if current_position.piece.color == WHITE and self.color == WHITE: #if current piece position is white and color is white
            movable = False #peice is not moveable
            return movable

        elif current_position.piece.color == BLACK and self.color == BLACK: #if current piece position is black and piece color is black
            movable = False #piece is not moveable
            return movable

        elif current_position.piece.color == WHITE and self.color == BLACK:#if the piece position color is white but the piece is black
            if current_position.rosette == True:#checks for a rosette
                movable = False #piece is not moveable
                return movable

        elif current_position.piece.color == BLACK and self.color == WHITE:#checks if the position color is black but the peice color is white
            if current_position.rosette == True: #checks for rosette
                movable = False #piece is not moveable
                return movable

    return movable


class BoardSquare:
    def __init__(self, x, y, entrance=False, _exit=False, rosette=False, forbidden=False):
        self.piece = None
        self.position = (x, y)
        self.next_white = None
        self.next_black = None
        self.exit = _exit
        self.entrance = entrance
        self.rosette = rosette
        self.forbidden = forbidden

    def load_from_json(self, json_string):
        import json
        loaded_position = json.loads(json_string)
        self.piece = None
        self.position = loaded_position['position']
        self.next_white = loaded_position['next_white']
        self.next_black = loaded_position['next_black']
        self.exit = loaded_position['exit']
        self.entrance = loaded_position['entrance']
        self.rosette = loaded_position['rosette']
        self.forbidden = loaded_position['forbidden']

    def jsonify(self):
        next_white = self.next_white.position if self.next_white else None
        next_black = self.next_black.position if self.next_black else None
        return {'position': self.position, 'next_white': next_white, 'next_black': next_black, 'exit': self.exit, 'entrance': self.entrance, 'rosette': self.rosette, 'forbidden': self.forbidden}
