rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

ARMGNU ?= aarch64-linux-gnu
COPS = -O3  -Wall
COPS += -nostdlib -nostartfiles -ffreestanding
COPS += -Iinclude -Isrc
COPS += -mgeneral-regs-only -mno-outline-atomics
ASMOPS = -Iinclude 

BUILD_DIR = build
SRC_DIR = src

C_FILES = $(call rwildcard,$(SRC_DIR),*.c)
ASM_FILES = $(call rwildcard,$(SRC_DIR),*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

# Generate img from object files
all: kernel8.img

# Clean build directory
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR) *.img
	@echo "Done cleaning build directory."
	@echo ""

# Compile C files
$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	@echo "Compiling C files..."
	@mkdir -p $(dir $@)
	@$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@
	@echo "Done compiling C files!"
	@echo ""

# Compile Assembly files
$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	@echo "Compiling assembly files..."	
	@mkdir -p $(dir $@)
	@$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@
	@echo "Done compiling assembly files!"
	@echo ""

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

# Generate img from object files
kernel8.img: $(SRC_DIR)/colt.ld $(OBJ_FILES)
	@echo "Linking object files..."
	@$(ARMGNU)-ld -T $(SRC_DIR)/colt.ld -o $(BUILD_DIR)/kernel8.elf  $(OBJ_FILES)
	@echo "Extracting code..."
	@$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img
	@echo "Done creating 'kernel8.img'!"
	@echo ""