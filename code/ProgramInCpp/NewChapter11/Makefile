TARGET = main
OBJS = reply.o
LIB = libreply.so
TESTOBJ = main.o
CXXFLAGS = -c -fPIC
LDFLAGS = -L. -lreply -Wl,-rpath $(@D)
SHARED = -shared

.PHONY: clean

$(TARGET):$(TESTOBJ) $(LIB)
	$(CXX) $< -o $@ $(LDFLAGS) 
$(LIB):$(OBJS)
	$(CXX) $(SHARED) $^ -o $@
%.o:%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
clean:
	$(RM) $(TARGET) $(OBJS) $(LIB) $(TESTOBJ)

