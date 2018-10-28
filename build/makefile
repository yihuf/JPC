cc = g++
exe = http_server
inc = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.cpp")
obj = $(src:%.cpp=%.o) 

$(exe): $(obj)
    $(cc) -o $(exe) $(obj)

%.o: %.cpp $(inc)
    $(cc) -c $< -o $@

clean:
    rm -rf $(obj) $(exe)
