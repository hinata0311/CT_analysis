# --- Directories ---
BUILD_DIR := build
LIB_DIR := $(BUILD_DIR)/lib
OBJ_DIR := $(BUILD_DIR)/obj
DICT_DIR := $(BUILD_DIR)/dict

# --- Compiler and Flags ---
CXX=`root-config --cxx`
CXXFLAGS=`root-config --cflags` 
LDFLAGS=`root-config --ldflags`
LDLIBS = `root-config --glibs` 

# --- Project Files ---
SOURCES := src/RunControl.cpp src/ce65TreeReader.cpp src/Cluster.cpp
INCLUDES := -Iinc/
HEADDIR := inc/
HEADERS := $(wildcard $(HEADDIR)*.h)
OBJECTS := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE := $(BUILD_DIR)/run_basic_analysis

# --- Dictionary Files ---
DICT_LIB := $(LIB_DIR)/libce65dict.so
DICT_SRC := $(BUILD_DIR)/ce65dict.cxx
DICT_PCM := $(LIB_DIR)/ce65dict_rdict.pcm
DICT_HEADERS := inc/CE65Event.h inc/Cluster.h
DICT_LINKDEF := $(HEADDIR)LinkDef.h

# --- Targets ---
.PHONY: all clean docs

all: $(EXECUTABLE)

# Make all necessary directories
$(BUILD_DIR) $(LIB_DIR) $(OBJ_DIR) $(DICT_DIR):
	@mkdir -p $@

# Dictionary build rule
$(DICT_LIB): $(DICT_HEADERS) $(DICT_DIR) $(LIB_DIR) $(DICT_LINKDEF)
	@echo "Building dictionary library..."
	@rootcling -f $(DICT_SRC) -rml $@ -Iinc $(DICT_HEADERS) $(DICT_LINKDEF)
	@$(CXX) $(CXXFLAGS) -fPIC -shared -I. $(INCLUDES) $(DICT_SRC) -o $@ $(LDFLAGS) $(LDLIBS)

# Main executable build rule
$(EXECUTABLE): $(OBJECTS) $(DICT_LIB)
	@echo "Building executable..."
	@$(CXX) $(CXXFLAGS) -O2 -W $(INCLUDES) -o $@ $(OBJECTS) $(DICT_LIB) $(LDFLAGS) $(LDLIBS) -L$(LIB_DIR) -lce65dict

# Object file rule
$(OBJ_DIR)/%.o: src/%.cpp
	@echo "Building object file $<..."
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -O2 -W $(INCLUDES) -c $< -o $@

# Clean rule
clean:
	@echo "Cleaning project..."
	@rm -rf $(BUILD_DIR)
	@rm -f *.pcm *.d
	@rm -f $(HEADDIR)*_ACLiC_dict_rdict.pcm
	@rm -rf $(HEADDIR)LinkDef.h.d
	@rm -rf $(HEADDIR)CE65Event.h.d
	@rm -rf $(HEADDIR)Cluster.h.d
	@rm -rf ./AutoDict*

docs:
	doxygen Doxyfile
