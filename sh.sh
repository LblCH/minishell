function check
{
	        echo "usage: hw14.sh option argument
			Please enter one or more options or arguments."
			        exit
				}
				function date
				{
					        if [[ $myvar == "-d" ]]
								        then date "+%d %B,%Y"
											        fi
												}
												function host
												{
													        if [[ $myvar == "-h" ]]
																        then hostname
																			        fi
																				}
																				function who
																				{
																					        if [[ $myvar == "-w" ]]
																								        then whoami
																											        fi
																												}
																												function help
																												{
																													        if [[ $myvar == "-help" ]]
																																        then echo "
																																			valid options:
																																			-d = display today's date in day-month-year format
																																			-h = display name of computer you are currently working on
																																			-w = display who you are logged in as
																																			arguments:
																																			Any argument entered is checked to see if it is a file name
																																			"
																																			        fi
																																				}
																																				if [ $# -le 0 ]
																																				then check
																																				fi
																																				for myvar
																																				do
																																					        if [[ $myvar == "-"* ]]
																																								        then date; host; who; help
																																											        fi
																																												done
