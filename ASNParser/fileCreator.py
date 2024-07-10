import asn1vnparser
import os

PROFILE_NAME = "profile"

# Create a directory named "profile"
if not os.path.exists(PROFILE_NAME):
    # Create the directory
    os.mkdir(PROFILE_NAME)

FILE = open("profile.txt", "r")
fileContents = FILE.read()

# Parsing to change to dictionary format in python
parsedContent = asn1vnparser.parse_asn1_value_assignments(fileContents)

# Looping over complete profile 
for section in parsedContent: 

    # Extracting value from inside 
    value_dict = section.value

    # Looping over the dictionary to identify if information needs to be extracted 
    for first_key, first_value in value_dict.items():
        
        # Skipping certain cases 
        if first_key in ("header", "pukCodes", "pinCodes", "genericFileManagement", "akaParameter", "cdmaParameter", "securityDomain", "rfm", "end"):
            continue
        
        # if first_key in ("telecom"):

        # Parsing data inside 
        for second_key, second_value in first_value.items():

            # Try for handling exception    
            try: 
                for third_key, third_value in second_value[0].items():
                    if third_key == "fileDescriptor":
                        
                        #Create a master file folder if it doesn't exist
                        master_folder = os.path.join(PROFILE_NAME, first_key)

                        if not os.path.exists(master_folder):
                            # Create the directory
                            os.mkdir(master_folder)

                        # Create files
                        FILE_PATH = os.path.join(master_folder, second_key)
                        
                        # Save the data to a text file
                        with open(FILE_PATH, "w") as f:
                            data = []
                            for k, v in third_value.items():
                                if k in ['fileID', 'lcsi', 'securityAttributesReferenced', 'efFileSize', 'shortEFID']:
                                    data.append(str(v))
                            f.write("\n".join(data))

            except:
                pass 


# Looping over the structure to create required filesystem 
# print(parsedContent[2].value)

# parsed_content = parsedContent[2]
# value_dict = parsed_content.value

# for key, value in value_dict.items():
#     print(key)
#     print(value["puk-Header"])
    