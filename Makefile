###############################################################################
# Makefile
#
# Copyright (C) 2017  WANG YIFU
#
# Auther: Wang Yifu
#
# Note: This is Makefile.
#
###############################################################################

# Compiler
CC = gcc

# Source file directory
DISPLAY_SRC_DIR = ./src/Display/
EFFECTS_SRC_DIR = ./src/Effects/
APP_SRC_DIR = ./src/App/
SIMULATOR_SRC_DIR = ./src/Simulator/

# Object file directory
DISPLAY_OBJ_DIR = ./obj/Display/
EFFECTS_OBJ_DIR = ./obj/Effects/
APP_OBJ_DIR = ./obj/App/
SIMULATOR_OBJ_DIR = ./obj/Simulator/

ALL_OBJS = $(DISPLAY_OBJ_DIR)LedAct.o $(DISPLAY_OBJ_DIR)LedEffect.o $(DISPLAY_OBJ_DIR)LedProcess.o \
           $(EFFECTS_OBJ_DIR)EffectDown.o $(EFFECTS_OBJ_DIR)EffectFixed.o $(EFFECTS_OBJ_DIR)EffectLaser.o \
           $(EFFECTS_OBJ_DIR)EffectLeft.o $(EFFECTS_OBJ_DIR)EffectRight.o $(EFFECTS_OBJ_DIR)EffectScroll.o \
           $(EFFECTS_OBJ_DIR)EffectSnow.o $(EFFECTS_OBJ_DIR)EffectUp.o $(APP_OBJ_DIR)Main.o \
           $(SIMULATOR_OBJ_DIR)Simulator.o

all : ${ALL_OBJS}
	$(CC) -o ledsim $(ALL_OBJS) -lpthread -lncurses

$(DISPLAY_OBJ_DIR)LedAct.o : $(DISPLAY_SRC_DIR)LedAct.c
	$(CC) -c -o $(DISPLAY_OBJ_DIR)LedAct.o $(DISPLAY_SRC_DIR)LedAct.c

$(DISPLAY_OBJ_DIR)LedEffect.o : $(DISPLAY_SRC_DIR)LedEffect.c
	$(CC) -c -o $(DISPLAY_OBJ_DIR)LedEffect.o $(DISPLAY_SRC_DIR)LedEffect.c

$(DISPLAY_OBJ_DIR)LedProcess.o : $(DISPLAY_SRC_DIR)LedProcess.c
	$(CC) -c -o $(DISPLAY_OBJ_DIR)LedProcess.o $(DISPLAY_SRC_DIR)LedProcess.c

$(EFFECTS_OBJ_DIR)EffectDown.o : $(EFFECTS_SRC_DIR)EffectDown.c
	$(CC) -c -o $(EFFECTS_OBJ_DIR)EffectDown.o $(EFFECTS_SRC_DIR)EffectDown.c

$(EFFECTS_OBJ_DIR)EffectFixed.o : $(EFFECTS_SRC_DIR)EffectFixed.c
	$(CC) -c -o $(EFFECTS_OBJ_DIR)EffectFixed.o $(EFFECTS_SRC_DIR)EffectFixed.c

$(EFFECTS_OBJ_DIR)EffectLaser.o : $(EFFECTS_SRC_DIR)EffectLaser.c
	$(CC) -c -o $(EFFECTS_OBJ_DIR)EffectLaser.o $(EFFECTS_SRC_DIR)EffectLaser.c

$(EFFECTS_OBJ_DIR)EffectLeft.o : $(EFFECTS_SRC_DIR)EffectLeft.c
	$(CC) -c -o $(EFFECTS_OBJ_DIR)EffectLeft.o $(EFFECTS_SRC_DIR)EffectLeft.c

$(EFFECTS_OBJ_DIR)EffectRight.o : $(EFFECTS_SRC_DIR)EffectRight.c
	$(CC) -c -o $(EFFECTS_OBJ_DIR)EffectRight.o $(EFFECTS_SRC_DIR)EffectRight.c

$(EFFECTS_OBJ_DIR)EffectScroll.o : $(EFFECTS_SRC_DIR)EffectScroll.c
	$(CC) -c -o $(EFFECTS_OBJ_DIR)EffectScroll.o $(EFFECTS_SRC_DIR)EffectScroll.c

$(EFFECTS_OBJ_DIR)EffectSnow.o : $(EFFECTS_SRC_DIR)EffectSnow.c
	$(CC) -c -o $(EFFECTS_OBJ_DIR)EffectSnow.o $(EFFECTS_SRC_DIR)EffectSnow.c

$(EFFECTS_OBJ_DIR)EffectUp.o : $(EFFECTS_SRC_DIR)EffectUp.c
	$(CC) -c -o $(EFFECTS_OBJ_DIR)EffectUp.o $(EFFECTS_SRC_DIR)EffectUp.c

$(APP_OBJ_DIR)Main.o : $(APP_SRC_DIR)Main.c
	$(CC) -c -o $(APP_OBJ_DIR)Main.o $(APP_SRC_DIR)Main.c

$(SIMULATOR_OBJ_DIR)Simulator.o : $(SIMULATOR_SRC_DIR)Simulator.c
	$(CC) -c -o $(SIMULATOR_OBJ_DIR)Simulator.o $(SIMULATOR_SRC_DIR)Simulator.c

.PHONY : clean
clean :
	@find $(DISPLAY_OBJ_DIR) -name '*.o' | xargs rm -rf
	@find $(EFFECTS_OBJ_DIR) -name '*.o' | xargs rm -rf
	@find $(APP_OBJ_DIR) -name '*.o' | xargs rm -rf
	@find $(SIMULATOR_OBJ_DIR) -name '*.o' | xargs rm -rf
	@find ./ -name 'ledsim' | xargs rm -rf
