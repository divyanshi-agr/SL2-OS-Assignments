#!/bin/sh

filename=0
while (true)
do
    #Printing Menu

    echo "---------------------------"
    echo "         MENU              "
    echo "---------------------------"
    echo "1. Create File"
    echo "2. Insert records in file"
    echo "3. Display File"
    echo "4. Search record"
    echo "5. Delete a record from File"
    echo "6. Update File"
    echo "7. Exit"
    echo "---------------------------"
    echo "Choose an option:"
    read option 

    case $option in

        1 )   echo "Enter name of file to be created: "
              read filename
              len=${#filename}

              if [ $len -gt 0 ]
              then  
                    if [ -f $filename ]
                    then echo "File already exists!\n"
                    else
                        touch $filename
                        echo "SR.\t\tDEPT\t\tHOD\t\tTOTAL STUDENTS" >> $filename
                        echo "File successfully created!\n" 
                    fi
               else 
                    echo "File name can't be empty!\n"
              fi
        ;;


        2 )   echo "Enter no. of records you want to insert:"
              read recs
              
              while [ $recs -gt 0 ]
              do

                    while (true)
                    do
                        echo "Enter record no.:"
                        read srno
                        len_srno=${#srno}
                        if [ $len_srno -gt 0 ]
                        then break 1
                        else   
                            echo "You need to enter record no.!"
                        fi
                    done

                    while (true)
                    do
                        echo "Enter department name:"
                        read dept
                        len_dept=${#dept}
                        if [ $len_dept -gt 0 ]
                        then break 1
                        else   
                            echo "You need to enter dept name!"
                        fi
                    done

                    while (true)
                    do
                        echo "Enter HOD of this department:"
                        read hod
                        len_hod=${#hod}
                        if [ $len_hod -gt 0 ]
                        then break 1
                        else   
                            echo "You need to enter HOD's name!"
                        fi
                    done

                    while (true)
                    do
                        echo "Enter no. of students in this dept:"
                        read stud
                        len_stud=${#stud}
                        if [ $len_stud -gt 0 ]
                        then break 1
                        else   
                            echo "You need to enter total students!"
                        fi
                    done

                    echo "$srno\t\t$dept\t\t$hod\t\t$stud" >> $filename 
                    recs=$((recs-1))      
              done          
        ;;


        3 )   if [ -f $filename ]
             then 
                    echo "The database is: \n"
                    cat $filename 
             else
                    echo "Database doesn't exist!!\n"
             fi          
        ;;

        4 )   read -p "Enter the name to be searched:" search_name
              lol="$(grep -i "$search_name" $filename)"
              if [ "$lol" ]
              then
                 echo "Record found!"
                 echo "$lol"
              else echo "Record not found!"
              fi       
        ;;

        5 )   read -p "Enter department to be deleted:" delete_dept
              sed -i "/$delete_dept/d" $filename
              echo "\nRecord deleted successfully!"       
        ;;

        6 )   echo "Choose which attribute you want to update:"
              echo "1.Department name"
              echo "2.HOD name"
              echo "3.Total students"
              read choice

              if [ $choice -le 0 || $choice -gt 4 ]
              then echo "Please enter valid option!"
              else
                    case $choice in
                    1 ) read -p "Enter department name of record you wanna update : " dept_name
                        read -p "Enter new department name : " newdept
                        sed -i "s/$dept_name/$newdept/g" $filename
                        echo "Record updated successfully!"

                    ;;

                    2 ) read -p "Enter HOD name of record you wanna update : " hod_name
                        read -p "Enter new HOD name : " newhod
                        sed -i "s/$hod_name/$newhod/g" $filename
                        echo "Record updated successfully!"

                    ;;

                    3 ) read -p "Enter total students of record you wanna update : " tot_studs
                        read -p "Enter new total students : " newstuds
                        sed -i "s/$tot_studs/$newstuds/g" $filename
                        echo "Record updated successfully!"

                    ;;

                    esac

              fi
        ;;
        
        7 )   exit 0 ;;
        * )   echo "Wrong option!" ;;

    esac


done
    

#OUTPUT:
# divyanshi-agr@DESKTOP-Q7MB9VU:~/Shell_Programs$ bash a1.sh
# --------------------------- 
#          MENU
# --------------------------- 
# 1. Create File
# 2. Insert records in file   
# 3. Display File
# 4. Delete a record from File
# 5. Update File
# 6. Exit
# --------------------------- 
# Choose an option:
# 1
# Enter name of file to be created: 
# f1
# File successfully created!  

# --------------------------- 
#          MENU
# --------------------------- 
# 1. Create File
# 2. Insert records in file   
# 3. Display File
# 4. Delete a record from File
# 5. Update File
# 6. Exit
# --------------------------- 
# Choose an option:
# 2
# Enter no. of records you want to insert:
# 2
# Enter department name:

# You need to enter dept name!
# Enter department name:      
# IT
# Enter HOD of this department:

# You need to enter HOD's name!
# Enter HOD of this department:
# a
# Enter no. of students in this dept:

# You need to enter total students!  
# Enter no. of students in this dept:
# 123
# Enter department name:
# CS
# Enter HOD of this department:
# b
# Enter no. of students in this dept:

# You need to enter total students!
# Enter no. of students in this dept:
# 565
# ---------------------------
#          MENU
# ---------------------------
# 1. Create File
# 2. Insert records in file
# 3. Display File
# 4. Delete a record from File
# 5. Update File
# 6. Exit
# ---------------------------
# Choose an option:
# 3
# The database is: 

# DEPT            HOD             TOTAL STUDENTS
# IT              a               123
# CS              b               565
# ---------------------------
#          MENU
# ---------------------------
# 1. Create File
# 2. Insert records in file
# 3. Display File
# 4. Delete a record from File
# 5. Update File
# 6. Exit
# ---------------------------
# Choose an option:
# 2
# Enter no. of records you want to insert:
# 1
# Enter department name:
# ENTC
# Enter HOD of this department:
# c
# Enter no. of students in this dept:
# 322
# ---------------------------
#          MENU
# ---------------------------
# 1. Create File
# 2. Insert records in file
# 3. Display File
# 4. Delete a record from File
# 5. Update File
# 6. Exit
# ---------------------------
# Choose an option:
# 3
# The database is: 

# DEPT            HOD             TOTAL STUDENTS
# IT              a               123
# CS              b               565
# ENTC            c               322
# ---------------------------
#          MENU
# ---------------------------
# 1. Create File
# 2. Insert records in file
# 3. Display File
# 4. Delete a record from File
# 5. Update File
# 6. Exit
# ---------------------------
# Choose an option:
# 1
# Enter name of file to be created:
# f1
# File already exists!

# ---------------------------
#          MENU
# ---------------------------
# 1. Create File
# 2. Insert records in file
# 3. Display File
# 4. Delete a record from File
# 5. Update File
# 6. Exit
# ---------------------------
# Choose an option:
# 6
# divyanshi-agr@DESKTOP-Q7MB9VU:~/Shell_Programs$ 