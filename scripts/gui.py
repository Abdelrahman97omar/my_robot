
from geometry_msgs.msg import Pose
from std_msgs.msg import String
from scipy.spatial.transform import Rotation as R
import tkinter as tk
import rospy
import numpy as np

rospy.init_node('gui_goal_sender', anonymous=True)
pub = rospy.Publisher('gui_action_topic_send_table', Pose, queue_size=10) # Publish goal to client
goal = Pose()

Home_pose   =(0.5,0.5,0)
Table_1_pose=(6.4,2.4,0)
Table_2_pose=(6.2,-0.75,0)
Table_3_pose=(6.2,-4,0)
Casher_pose =(4,4,0)
isOnlyGoal=False
Goals_qeue=[]  # qeue of the goals to be sent to ros 
labels=[]      # qeue of labels


# Function to send the goal to the robot
def send_goal(goTo):
        global Goals_qeue
        quaternion = euler_to_quaternion(goTo[2])
        # goal.header.frame_id = "map"  # Or use whatever your robot's frame is
        # goal.header.stamp = rospy.Time.now()
        goal.position.x = goTo[0]
        goal.position.y = goTo[1]
        goal.orientation.x= quaternion[0]
        goal.orientation.y= quaternion[1]
        goal.orientation.z= quaternion[2]
        goal.orientation.w= quaternion[3]
        pub.publish(goal)
        
def stateCB(data):
    global isOnlyGoal

    # if isOnlyGoal: # 
    if data.data=='Done' and len(Goals_qeue)>0:
        send_goal(Goals_qeue[0])
        deleteFromGoalsQeue()
    elif data.data=='Done' and len(Goals_qeue)==0:
        isOnlyGoal=False
        send_goal(Home_pose)

state_sub = rospy.Subscriber('GUI_Cleint_state_topic',String,stateCB)

def add_table1():
    global isOnlyGoal
    add_to_qeue(Table_1_pose)
    label_update('Table 1')
    if not isOnlyGoal:
        isOnlyGoal=True
        send_goal(Table_1_pose)
        print("goal is sent")

def add_table2():
    global isOnlyGoal
    add_to_qeue(Table_2_pose)
    label_update('Table 2')
    if not isOnlyGoal:
        isOnlyGoal=True
        send_goal(Table_2_pose)

def add_table3():
    global isOnlyGoal  
    add_to_qeue(Table_3_pose)
    label_update('Table 3')
    if not isOnlyGoal:
        isOnlyGoal=True
        send_goal(Table_3_pose)

def add_cashir():
    global isOnlyGoal    
    add_to_qeue(Casher_pose)
    label_update('Casher')
    if not isOnlyGoal:
        isOnlyGoal=True
        send_goal(Casher_pose)

# #==============================================================#

# Setting up the Tkinter window
GuiWindow = tk.Tk()
GuiWindow.title("Robot Goal Sender")


Table_1_button = tk.Button(GuiWindow, text="Table 1", command=add_table1)
Table_2_button = tk.Button(GuiWindow, text="Table 2", command=add_table2)
Table_3_button = tk.Button(GuiWindow, text="Table 3", command=add_table3)
cashir_button  = tk.Button(GuiWindow, text="Cashir", command=add_cashir)

Table_1_button.grid(row=0, column=0, columnspan=2)
Table_2_button.grid(row=1, column=0, columnspan=2)
Table_3_button.grid(row=2, column=0, columnspan=2)
cashir_button.grid(row=3, column=0, columnspan=2)


def label_update(label_name):
    if len(labels) != 5:
        label = tk.Label(GuiWindow, text=label_name)
        row_index = len(labels) + 4  # Start placing labels below the buttons
        label.grid(row=row_index, column=0, columnspan=2)
        labels.append(label)

# This function to add goals to the qeue of goals
def add_to_qeue(pose):
    global Goals_qeue
    if len(Goals_qeue)<5:
        Goals_qeue.append(pose)
        print(f"The currunt goals qeue is: {Goals_qeue} and the qeue length is {len(Goals_qeue)}")
    else:
        print("You have qeue of 5")

def deleteFromGoalsQeue():
    print("in remove from qeue")
    Goals_qeue.pop(0)
    label = labels.pop(0)
    label.destroy()
    print(f"In deletefromgoalsqeue and the currunt goals qeue is: {Goals_qeue} and the qeue length is {len(Goals_qeue)}")


def euler_to_quaternion(theta):
    rotation = R.from_euler('z', theta, degrees=True)  # 'z' axis, theta in degrees
    # Convert to quaternion
    quaternion = rotation.as_quat()  # [x, y, z, w]
    return quaternion

GuiWindow.mainloop()
