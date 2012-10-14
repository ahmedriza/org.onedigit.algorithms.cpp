CXX = clang++
CXXFLAGS = -std=c++11 -stdlib=libc++
DEPS := $(OBJECTS:.o=.deps)
BUILDDIR = Debug

OBJECTS = $(BUILDDIR)/TestSuite.o
TARGET = $(BUILDDIR)/TestSuite

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(BUILDDIR)/*.o $(TARGET)

-include $(DEPS)

.PHONY: clean