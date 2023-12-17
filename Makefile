CXX=g++
CPPFILES=main.cpp TuringMachine.cpp
CXXFLAGS=-Wall -Wextra
OBJDIR=./obj
OBJFILES=$(patsubst %.cpp,$(OBJDIR)/%.o, $(CPPFILES))
BINARY=turing

all: $(BINARY)

$(BINARY): $(OBJFILES)
	@echo "Creating binary.."
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJFILES): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

run: $(BINARY)
	@./$(BINARY)

clean:
	@echo "Removing object files.."
	rm -rf $(OBJDIR) 
	@echo "Removing binary.."
	rm -f $(BINARY)

