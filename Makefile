CXX = clang++
CXXFLAGS = -std=c++11 -stdlib=libc++
BUILDDIR = Debug

OBJECTS = $(BUILDDIR)/TestSuite.o
TARGET = $(BUILDDIR)/TestSuite

DEPS := $(OBJECTS:.o=.deps)

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(BUILDDIR)/*.o $(TARGET)

-include $(DEPS)

.PHONY: clean