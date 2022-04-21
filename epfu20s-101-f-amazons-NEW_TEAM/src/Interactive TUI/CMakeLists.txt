
project(src C)

set(CMAKE_C_STANDARD 99)

add_executable(src interactiveGame.c Board/boardUtils.c Board/boardUtils.h UTILS/constants.h UTILS/structs.h Moves/movesUtils.c Moves/movesUtils.h Moves/movesPossibility.c Moves/movesPossibility.h Players/playersUtils.c Players/playersUtils.h UTILS/IOUtils.c UTILS/IOUtils.h)