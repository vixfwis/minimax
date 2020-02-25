#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../board.hpp"

TEST_CASE("Board class tests", "[minimax]"){
    Board b;
    b.setValue(0, Board::PLAYER);
    b.setValue(1, Board::PLAYER);
    b.setValue(3, Board::PLAYER);
    b.setValue(4, Board::AI);
    b.setValue(6, Board::AI);

    SECTION("isGameEnded check for not found"){
        REQUIRE(b.isGameEnded() == Board::UNDEFINED);
    }

    SECTION("isGameEnded check for player wins"){
        b.setValue(2, Board::PLAYER);
        REQUIRE(b.isGameEnded() == Board::PLAYER);
    }

    SECTION("isGameEnded check for ai wins"){
        b.setValue(2, Board::AI);
        REQUIRE(b.isGameEnded() == Board::AI);
    }

    SECTION("isGameEnded empty board check"){
        Board b2;
        REQUIRE(b.isGameEnded() == Board::UNDEFINED);
    }

    SECTION("isGameEnded draw check"){
        b.setValue(1, Board::AI);
        b.setValue(2, Board::PLAYER);
        b.setValue(5, Board::PLAYER);
        b.setValue(7, Board::PLAYER);
        b.setValue(8, Board::AI);
        REQUIRE(b.isGameEnded() == Board::EMPTY);
    }

    SECTION("contains returns true if passed indices contain only passed values in any order"){
        REQUIRE(b.contains(0, 1, 3, Board::PLAYER));
        REQUIRE(b.contains(4, 0, 2, Board::PLAYER, Board::AI));
        REQUIRE(b.contains(4, 0, 2, Board::AI));
        REQUIRE(b.contains(0, 0, 2, Board::PLAYER, Board::EMPTY));
        REQUIRE_FALSE(b.contains(0, 0, 2, Board::PLAYER, Board::EMPTY, Board::AI));
        REQUIRE_FALSE(b.contains(0, 1, 3, Board::PLAYER, Board::AI));
    }

    SECTION("contains works with duplicate Status params"){
        REQUIRE_FALSE(b.contains(4, 0, 2, Board::PLAYER, Board::AI, Board::PLAYER));
        REQUIRE_FALSE(b.contains(4, 0, 2, Board::AI, Board::PLAYER, Board::PLAYER));
        REQUIRE(b.contains(0, 1, 2, Board::PLAYER, Board::PLAYER, Board::EMPTY));
        REQUIRE(b.contains(0, 1, 2, Board::EMPTY, Board::PLAYER, Board::PLAYER));
    }

    SECTION("evaluate return score based on board state"){
        REQUIRE(b.evaluate() == 0);
        // remove one double from player with AI win condition
        b.setValue(2, Board::AI);
        REQUIRE(b.evaluate() == -100);
        // give player win condition
        b.setValue(2, Board::PLAYER);
        REQUIRE(b.evaluate() == 100);
    }
}
