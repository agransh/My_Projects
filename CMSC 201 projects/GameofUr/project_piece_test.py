from board_square import BoardSquare, UrPiece

""" Feel free to change these constants to whatever your project constants are going to be"""
WHITE = 'White'
BLACK = 'Black'


def standard_board_move_test():
    piece = UrPiece(WHITE, 'W')
    bs_1 = BoardSquare(1, 1)
    bs_1.piece = piece
    piece.position = bs_1

    print("=" * 10 + "Test Unobstructed Move" + "=" * 10)

    bs_2 = BoardSquare(1, 2)
    bs_3 = BoardSquare(1, 3)
    bs_4 = BoardSquare(1, 4)
    bs_5 = BoardSquare(1, 5)
    bs_1.next_white = bs_2

    if piece.can_move(1):
        print('One move test successful.')
    else:
        print('One move test failed.')

    bs_2.next_white = bs_3

    if piece.can_move(2):
        print('Two move test successful.')
    else:
        print('Two move test failed.')

    bs_3.next_white = bs_4

    if piece.can_move(3):
        print('Three move test successful.')
    else:
        print('Three move test failed.')

    bs_4.next_white = bs_5

    if piece.can_move(4):
        print('Four move test successful.')
    else:
        print('Four move test failed.')


def standard_board_non_move_test():
    print("=" * 10 + "Test Landing on Piece of Same Color" + "=" * 10)
    piece = UrPiece(WHITE, 'W')
    bs_1 = BoardSquare(1, 1)
    bs_1.piece = piece
    piece.position = bs_1

    bs_2 = BoardSquare(1, 2)
    bs_3 = BoardSquare(1, 3)
    bs_4 = BoardSquare(1, 4)
    bs_5 = BoardSquare(1, 5)
    bs_1.next_white = bs_2
    bs_2.piece = UrPiece(WHITE, 'W2')

    if not piece.can_move(1):
        print('One move test successful.')
    else:
        print('One move test failed.')

    bs_2.next_white = bs_3
    bs_3.piece = UrPiece(WHITE, 'W2')

    if not piece.can_move(2):
        print('Two move test successful.')
    else:
        print('Two move test failed.')

    bs_3.next_white = bs_4
    bs_4.piece = UrPiece(WHITE, 'W2')

    if not piece.can_move(3):
        print('Three move test successful.')
    else:
        print('Three move test failed.')

    bs_4.next_white = bs_5
    bs_5.piece = UrPiece(WHITE, 'W2')

    if not piece.can_move(4):
        print('Four move test successful.')
    else:
        print('Four move test failed.')


def board_entrance_test():
    print("=" * 10 + "Board Entrance Test" + "=" * 10)

    piece = UrPiece(WHITE, 'W')
    bs_1 = BoardSquare(1, 1)
    """
        YOU NEED TO SET THE WHITE START POSITION SOMEHOW RIGHT HERE!!!
        SET IT TO bs_1 and run this test.  
    """
    UrPiece.WhiteStarts.append(bs_1)
    bs_1.piece = piece
    piece.position = bs_1

    bs_2 = BoardSquare(1, 2)
    bs_3 = BoardSquare(1, 3)
    bs_4 = BoardSquare(1, 4)

    if piece.can_move(1):
        print('One move test successful.')
    else:
        print('One move test failed.')

    bs_1.next_white = bs_2

    if piece.can_move(2):
        print('Two move test successful.')
    else:
        print('Two move test failed.')

    bs_2.next_white = bs_3

    if piece.can_move(3):
        print('Three move test successful.')
    else:
        print('Three move test failed.')

    bs_3.next_white = bs_4

    if piece.can_move(4):
        print('Four move test successful.')
    else:
        print('Four move test failed.')


def board_exit_test():
    print("=" * 10 + "Board Exit Test" + "=" * 10)
    """
        YOU NEED TO SET THE WHITE EXIT POSITION SOMEHOW RIGHT HERE!!!
        SET IT TO bs_5 and run this test.  
    """
    piece = UrPiece(WHITE, 'W')
    bs_1 = BoardSquare(1, 1)
    bs_2 = BoardSquare(1, 2)
    bs_3 = BoardSquare(1, 3)
    bs_4 = BoardSquare(1, 4)
    bs_5 = BoardSquare(1, 5)
    bs_5.piece = piece
    piece.position = bs_5

    """
        YOU NEED TO SET THE WHITE START POSITION SOMEHOW RIGHT HERE!!!
        SET IT TO bs_1 and run this test.  
    """
    UrPiece.WhiteEnds.append(bs_5)

    """
        This one move would take the player's stone off the board
    """
    if piece.can_move(1):
        print('One move test successful.')
    else:
        print('One move test failed.')

    bs_1.next_white = bs_2

    """
        The rest of these tests should come back false since you cannot move the stone once it's off the board
    """
    if not piece.can_move(2):
        print('Two move test successful.')
    else:
        print('Two move test failed.')

    bs_2.next_white = bs_3

    if not piece.can_move(3):
        print('Three move test successful.')
    else:
        print('Three move test failed.')

    bs_3.next_white = bs_4

    if not piece.can_move(4):
        print('Four move test successful.')
    else:
        print('Four move test failed.')


def capture_test():
    print("=" * 10 + "Capture Test" + "=" * 10)
    piece = UrPiece(WHITE, 'W')
    bs_1 = BoardSquare(1, 1)
    bs_1.piece = piece
    piece.position = bs_1

    bs_2 = BoardSquare(1, 2)
    bs_3 = BoardSquare(1, 3)
    bs_4 = BoardSquare(1, 4)
    bs_5 = BoardSquare(1, 5)
    bs_1.next_white = bs_2
    bs_2.piece = UrPiece(BLACK, 'B2')

    if piece.can_move(1):
        print('One move test successful.')
    else:
        print('One move test failed.')

    bs_2.next_white = bs_3
    bs_3.piece = UrPiece(BLACK, 'B3')

    if piece.can_move(2):
        print('Two move test successful.')
    else:
        print('Two move test failed.')

    bs_3.next_white = bs_4
    bs_4.piece = UrPiece(BLACK, 'B4')

    if piece.can_move(3):
        print('Three move test successful.')
    else:
        print('Three move test failed.')

    bs_4.next_white = bs_5
    bs_5.piece = UrPiece(BLACK, 'B5')

    if piece.can_move(4):
        print('Four move test successful.')
    else:
        print('Four move test failed.')


def rosette_test():
    print("=" * 10 + "Rosette Test" + "=" * 10)
    piece = UrPiece(WHITE, 'W')
    piece = UrPiece(WHITE, 'W')
    bs_1 = BoardSquare(1, 1)
    bs_1.piece = piece
    piece.position = bs_1

    bs_2 = BoardSquare(1, 2)
    bs_3 = BoardSquare(1, 3)
    bs_4 = BoardSquare(1, 4)
    bs_5 = BoardSquare(1, 5)
    bs_1.next_white = bs_2
    bs_2.piece = UrPiece(BLACK, 'B2')
    bs_2.rosette = True

    if not piece.can_move(1):
        print('One move test successful.')
    else:
        print('One move test failed.')

    bs_2.next_white = bs_3
    bs_3.piece = UrPiece(BLACK, 'B3')
    bs_2.rosette = False
    bs_3.rosette = True

    if not piece.can_move(2):
        print('Two move test successful.')
    else:
        print('Two move test failed.')

    bs_3.next_white = bs_4
    bs_4.piece = UrPiece(BLACK, 'B4')
    bs_3.rosette = False
    bs_4.rosette = True

    if not piece.can_move(3):
        print('Three move test successful.')
    else:
        print('Three move test failed.')

    bs_4.next_white = bs_5
    bs_5.piece = UrPiece(BLACK, 'B5')
    bs_4.rosette = False
    bs_5.rosette = True

    if not piece.can_move(4):
        print('Four move test successful.')
    else:
        print('Four move test failed.')


def run_project_piece_tests():
    standard_board_move_test()
    standard_board_non_move_test()
    if input('Have you set the entrance position in the test function (to bs_1)? ').lower().strip() in ['y', 'yes']:
        board_entrance_test()
    if input('Have you set the exit position in the test function (to bs_5)? ').lower().strip() in ['y', 'yes']:
        board_exit_test()
    capture_test()
    rosette_test()


if __name__ == '__main__':
    run_project_piece_tests()
