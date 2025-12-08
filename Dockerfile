# Giselle Hernandez 
# Tiffany Nguyen 
# Docker file to build our scanner guardian container
FROM gcc:latest 

# setting work directory
WORKDIR /app 

# copying files over 
COPY . /app 

# compilation line 
RUN gcc -o fsguard scanner/format_string_guardian.c 

# running command
CMD ["./fsguard"]