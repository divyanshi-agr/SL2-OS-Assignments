#!/bin/sh
filename=0

#Creating a database
create_file () {
    awk 'BEGIN { print "Enter name of file to be created: "; }'
    read filename
    len=${#filename}

    if [ $len -gt 0 ]
    then  
        if [ -f $filename ]
        then awk 'BEGIN { print "File already exists!"; }'
        else
            touch $filename
            echo "SR.\t\tDEPT\t\tHOD\t\tTOTAL STUDENTS" >> $filename
            awk 'BEGIN { print "File successfully created!"; }' 
        fi
    else 
        awk 'BEGIN { print "File name cant be empty"; }'
    fi
}

#Inserting records in the database
insert_file () {
    awk 'BEGIN { print "Enter no. of records you want to insert: "; }'
    read recs
    
    while [ $recs -gt 0 ]
    do

        while (true)
        do
            read -p "Enter record no.:" srno
            len_srno=${#srno}
            if [ $len_srno -gt 0 ]
            then break 1
            else   
                echo "You need to enter record no.!"
            fi
        done

        while (true)
        do
            read -p "Enter department name:" dept
            len_dept=${#dept}
            if [ $len_dept -gt 0 ]
            then break 1
            else   
                echo "You need to enter dept name!"
            fi
        done

        while (true)
        do
            read -p "Enter HOD of this department:" hod
            len_hod=${#hod}
            if [ $len_hod -gt 0 ]
            then break 1
            else   
                echo "You need to enter HOD's name!"
            fi
        done

        while (true)
        do
            read -p "Enter no. of students in this dept:" stud
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
}

#Displaying the database
display_file () {
    if [ -f $filename ]
    then 
        awk 'BEGIN { print "The database is: "; }'
        awk '{print}' $filename 
    else
        awk 'BEGIN { print "Database does not exist!!\n"; }'
    fi 
}

 #Searching for a record in database
 search_file () {
    read -p "Enter the name to be searched:" search_name
    # awk '/"$search_name"/' $filename

    abc="$(grep -i "$search_name" $filename)"
    if [ "$abc" ]
    then
        echo "Record found!"
        echo "$abc"
    else echo "Record not found!"
    fi  
 }

 #Deleteing a record in database
 delete_file () {
    read -p "Enter department to be deleted:" delete_dept 
    dummy=0

  #Checking if the dept entered exists in the SECOND column (Department) or not.
  awk 'BEGIN {
            if($2 == "$delete_dept")   
            {
                dummy=1
            }
        }'   

        if [ dummy -eq 1 ]
        then sed -i "/$delete_dept/d" $filename
        echo "\nRecord deleted successfully!"
        else echo "\nRecord does not exist!"
        fi

 }

 #Modifying a record in database
 modify_file () {
    echo "Choose which attribute you want to update:"
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

            #Checking for the department in the database and then modifying it using gsub function of awk.
            awk 'BEGIN {
            if($2 == "$dept_name")
            {
                gsub(/"$dept_name"/,"$newdept",$2); 
                print "Record updated successfully!";            

            }
            else {
                print "Record does not exist!";
            }
        }'

        ;;

        2 ) read -p "Enter HOD name of record you wanna update : " hod_name
            read -p "Enter new HOD name : " newhod

            #Checking for the hod in the database and then modifying it using gsub function of awk.
            awk 'BEGIN {
            if($3 == "$hod_name")
            {
                gsub(/"$hod_name"/,"$newhod",$3); 
                print "Record updated successfully!"               

            }
            else {
                print "Record does not exist!";
            }
        }'

        ;;

        3 ) read -p "Enter total students of record you wanna update : " tot_studs
            read -p "Enter new total students : " newstuds

            #Checking for the total students in the database and then modifying it using gsub function of awk.
            awk 'BEGIN {
            if($4 == "$tot_studs")
            {
                gsub(/"$tot_studs"/,"$newstuds",$3); 
                print "Record updated successfully!"               

            }
            else {
                print "Record does not exist!";
            }
        }'

        ;;

        * ) echo "Wrong option !!" ;;

        esac

    fi
 }

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

        1 )  create_file ;;
        
        2 )  insert_file ;;
        
        3 )  display_file ;;
       
        4 )  search_file ;;
        
        5 )  delete_file ;;
        
        6 )  modify_file ;;     
        
        7 )   exit 0 ;;

        * )   echo "Wrong option!" ;;

    esac


done
    

