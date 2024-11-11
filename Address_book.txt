#!/bin/bash
fname='Adbook.txt'
touch $fname
cat $fname
a=1
while [ $a -eq 1 ]
do
    echo -e "Enter a choice -\n1) Insert\n2) Display\n3) Delete\n4) Modify"
    read ch
    case $ch in
        1)
            echo -e "\nEnter your name"
            read name
            echo -e "\nEnter phone number"
            read phone
            echo -e "\nEnter city"
            read city
            echo -e "\nEnter pin number"
            read pin
            echo -e "\nEnter state"
            read state
            echo -e "$name\t$phone\t$city\t$pin\t$state" >> $fname
            ;;
        2)
            if [ -s $fname ]
            then
                echo -e "Name\tPhone number\tCity\tPin\tState\n"
                cat $fname
            else
                echo -e "\nFile is empty"
            fi
            ;;
        3)
            echo -e "\nEnter name to delete record for"
            read name1
            grep -v $name1 $fname > temp
            if [ $? -eq 0 ]
            then
                echo -e "\nRecord deleted"
                mv temp $fname
            else
                echo -e "\nRecord not found"
            fi
            ;;
        4)
            echo -e "\nEnter record to modify"
            read name2
            no=$(grep -n "$name2" $fname | cut -c 1)
            if [ -z "$no" ]
            then
                echo -e "\nRecord not found"
            else
                echo -e "\nModifying line number :: $no"
                echo -e "\nEnter new record (format: Name\tPhone\tCity\tPin\tState)"
                read name3
                sed -i "$no s/.*/$name3/" $fname
                echo -e "\nRecord modified"
            fi
            ;;
    esac
done
