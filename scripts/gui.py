
from geometry_msgs.msg import PoseStamped
from scipy.spatial.transform import Rotation as R
import tkinter as tk
import rospy
import numpy as np

rospy.init_node('gui_goal_sender', anonymous=True)
pub = rospy.Publisher('/move_base_simple/goal', PoseStamped, queue_size=10)
goal = PoseStamped()

Table_1_pose=(3,3,0)
Table_2_pose=(2,2,0)
Table_3_pose=(3,3,0)
Casher_pose =(4,4,0)

my_qeue=()  # qeue of the goals to be sent to ros 
GUI_label_list_index=0


# Function to send the goal to the robot
def send_goal(goTo):
        global my_qeue
        quaternion = euler_to_quaternion(goTo[2])
        goal.header.frame_id = "map"  # Or use whatever your robot's frame is
        goal.header.stamp = rospy.Time.now()
        goal.pose.position.x = goTo[0]
        goal.pose.position.y = goTo[1]
        goal.pose.orientation.x= quaternion[0]
        goal.pose.orientation.y= quaternion[1]
        goal.pose.orientation.z= quaternion[2]
        goal.pose.orientation.w= quaternion[3]
        pub.publish(goal)
        

def add_table1():
    global GUI_label_list_index
    add_to_qeue(Table_1_pose)
    label_update(GUI_label_list_index,'Table 1')
    GUI_label_list_index=GUI_label_list_index+1
    send_goal(Table_1_pose)

def add_table2():
    global GUI_label_list_index
    add_to_qeue(Table_2_pose)
    label_update(GUI_label_list_index,'Table 2')
    GUI_label_list_index=GUI_label_list_index+1

def add_table3():
    global  GUI_label_list_index
    add_to_qeue(Table_3_pose)
    label_update(GUI_label_list_index,'Table 3')
    GUI_label_list_index=GUI_label_list_index+1

def add_cashir():
    global GUI_label_list_index
    add_to_qeue(Casher_pose)
    label_update(GUI_label_list_index,'Casher')
    GUI_label_list_index=GUI_label_list_index+1

# Setting up the Tkinter window
GuiWindow = tk.Tk()
GuiWindow.title("Robot Goal Sender")

# Labels and Entries for Goal Coordinates
# label_x = tk.Label(GuiWindow, text="X Coordinate:")
# label_x.grid(row=0, column=0)

# entry_x = tk.Entry(GuiWindow)
# entry_x.grid(row=0, column=1)
# #==============================================================#

Table_1_button = tk.Button(GuiWindow, text="Table 1", command=add_table1)
Table_2_button = tk.Button(GuiWindow, text="Table 2", command=add_table2)
Table_3_button = tk.Button(GuiWindow, text="Table 3", command=add_table3)
cashir_button  = tk.Button(GuiWindow, text="Cashir", command=add_cashir)

Table_1_button.grid(row=0, column=0, columnspan=2)
Table_2_button.grid(row=1, column=0, columnspan=2)
Table_3_button.grid(row=2, column=0, columnspan=2)
cashir_button.grid(row=3, column=0, columnspan=2)

qeue1 = tk.Label(GuiWindow, text="No request")
qeue2 = tk.Label(GuiWindow, text="No request")
qeue3 = tk.Label(GuiWindow, text="No request")
qeue4 = tk.Label(GuiWindow, text="No request")
qeue5 = tk.Label(GuiWindow, text="No request")

qeue1.grid(row=4,column=0)
qeue2.grid(row=5, column=0)
qeue3.grid(row=6, column=0)
qeue4.grid(row=7, column=0)
qeue5.grid(row=8, column=0)

def label_update(index,label_name):
    if index==0:
        qeue1.config(text=label_name)
    if index==1:
        qeue2.config(text=label_name)
    if index==2:
        qeue3.config(text=label_name)
    if index==3:
        qeue4.config(text=label_name)
    if index==4:
        qeue5.config(text=label_name)
        
def add_to_qeue(pose):
    global GUI_label_list_index,my_qeue
    if GUI_label_list_index<5:
        my_qeue=my_qeue+(pose,)
        print(my_qeue)

    else:
        print("You have qeue of 5")
        
def euler_to_quaternion(theta):
    # Create a rotation object based on Euler angles
    rotation = R.from_euler('z', theta, degrees=True)  # 'z' axis, theta in degrees
    # Convert to quaternion
    quaternion = rotation.as_quat()  # [x, y, z, w]
    return quaternion

GuiWindow.mainloop()
