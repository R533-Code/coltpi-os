rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

ARMGNU ?= aarch64-linux-gnu
ARMDISASM ?= aarch64-linux-gnu-objdump
COPS = -Wall -fPIC
COPS += -nostdlib -nostartfiles -ffreestanding
COPS += -Isrc
COPS += -mno-outline-atomics
COPS += $(if $(findstring release,$(CONFIG)),-O3,-g -Og -DCOLTPI_DEBUG)
ASMOPS = -Isrc

CONFIG ?= release
BUILD_DIR = $(if $(findstring release,$(CONFIG)),build/release,build/debug)
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
	@$(ARMGNU)-ld -T $(SRC_DIR)/colt.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	@echo "Extracting code..."
	@$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary $(BUILD_DIR)/kernel8.img
	@echo "Done creating 'kernel8.img'!"
	@echo ""

resize: kernel8.img
	$(eval CURRENT_SIZE = $(shell stat -c%s "$(BUILD_DIR)/kernel8.img"))
	$(eval NEXT_POWER_OF_TWO = $(shell python3 -c "import math;print(2**(math.ceil(math.log($(CURRENT_SIZE), 2))))"))
	@echo "The current size of 'kernel8.img' is $(CURRENT_SIZE)."
	@echo "Resizing 'kernel8.img' from $(CURRENT_SIZE) to $(NEXT_POWER_OF_TWO)..."
	@qemu-img resize -fraw "$(BUILD_DIR)/kernel8.img" "$(NEXT_POWER_OF_TWO)"
	@echo ""

qemu: resize
	@echo "Starting qemu..."
	@qemu-system-aarch64 -s -S -machine virt -cpu cortex-a72 -smp 6 -m 4G -kernel $(BUILD_DIR)/kernel8.elf -append "root=/dev/vda2 rootfstype=ext4 rw panic=0 console=ttyAMA0" -drive format=raw,file=$(BUILD_DIR)/kernel8.elf,if=none,id=hd0,cache=writeback
	@echo "Closed qemu!"

disasm: kernel8.img
	@echo "Disassembling kernel8.elf..."
	@$(ARMDISASM) -d -f $(BUILD_DIR)/kernel8.elf