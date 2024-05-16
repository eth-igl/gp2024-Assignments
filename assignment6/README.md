# Assignment 6: Skinning & Skeletal Animation

Name: 'Your real name'

Legi-Nr: 'Your legi number'


## Required results
Edit this 'README.md' file to report all your results. Use the `./res` folder to store your results.

### Tasks

1. Read Sec. 1 carefully to get familar with the data format, problem formulation, and mathematical background.
2. (Task 2) two theoretical discussions 
3. (Task 3) visualize the animation of the input skeleton of the hand shape from two types of input rotations (sequence and )
4. (Task 4) compute harmonic skinning weights on selected handles
5. (Task 5) per-vertex LBS + rotation/translation + Lerp
6. (Task 6) per-vertex LBS + dual quaternion + Nlerp
7. (Task 7) per-face LBS + averaging rotation + Poisson Stitching
8. (Task 8.1) context-aware per-vertex LBS
9. (optional Task 8.2) context-aware per-face LBS
 
### Important Note
1. We do not provide template code for this assignment - feel free to use previous template code if you want
2. You can use any functions in libigl, and its dependencies (and [libhedra](https://avaxman.github.io/libhedra/) if you want).
3. You are allowed to use your previous code (for example, you will find the Poisson Stitching technqiue quite similar to Deformation Transfer that you have implemented in Assignment 5; and also the provided handle selection in A5 might inspire you to design your handle selection tool in Task 4).
4. You are allowed to modify this report freely (but please try to stick to some table format of orangizing figures to avoid a 20-page long report)
5. Please feel free to try other skeletal animation/deformation data you can find online if you find the provided animation is not cool enough (for example [here](https://www.mixamo.com/#/), but note that they might be in different data format than the provide ones).
6. Please try to keep your code clean and self-explained (with necessary comments), since we will grade this assignment based on your code as well.

## Reports

### Task 2: Rotation Representation discussion
#### Task 2.1. compare different rotation representations

| Representions        |  Short Description  |     pros            |      cons           |
| :------------------: |:------------------: |:------------------: |:------------------: |
| rotation matrix      | xxxxxx              |xxxxxx               | xxxxxx              |
| euler angles         | xxxxxx              |xxxxxx               | xxxxxx              |
| axis angle           | xxxxxx              |xxxxxx               | xxxxxx              |
| quaternions          | xxxxxx              |xxxxxx               | xxxxxx              |

#### Task 2.2. Theoretical question for dual quaternions

| Euler angles -> rotation  matrix |  rotation matrix -> quaternion  |    quaternion + translation -> dual quaternion   |
| :------------------------------: |:------------------------------: |:-----------------------------------------------: |
| xxxxx                            | xxxxxx                          |xxxxxx                                            | 

### Task 3: animation of the skeleton
|                       rotaton sequence                       |               interpolation to target rotation                |
|:-------------------------------------------------------------:|:-------------------------------------------------------------:|
| <img align="center"  src="./res/placeholder.gif" width="300"> | <img align="center"  src="./res/placeholder.gif" width="300"> |

### Task 4: computing harmonic skinning weights on selected handles
#### Task 4.1. handle selection
| shape name           |  joint 1            |  joint 2            |  joint 3            |
| :------------------: |:------------------: |:------------------: |:------------------: |
| hand | <img align="center"  src="./res/placeholder.png" width="300">  | <img align="center"  src="./res/placeholder.png" width="300"> | <img align="center"  src="./res/placeholder.png" width="300"> |


#### Task 4.2. skinning weights visualization
| shape name           |  joint 1            |  joint 2            |  joint 3            |
| :------------------: |:------------------: |:------------------: |:------------------: |
| hand | <img align="center"  src="./res/placeholder.png" width="300">  | <img align="center"  src="./res/placeholder.png" width="300"> | <img align="center"  src="./res/placeholder.png" width="300"> |

### Task 5/6/7: skeletal animation 
|                   Task 5: Linear Blend Skinning                    |                   Task 6: Dual Quaternion Skinning                   |     Task 7: per-face + averaging quaternions     |
|:-------------------------------------------------------------:|:-------------------------------------------------------------:|:-------------------------------------------------------------:|
| <img align="center"  src="./res/placeholder.gif" width="300"> | <img align="center"  src="./res/placeholder.gif" width="300"> | <img align="center"  src="./res/placeholder.gif" width="300"> |


Your comments (how these setups different from each other, and please compare the visual effects)

| Task 5: Linear Blend Skinning   | Task 6: Dual Quaternion Skinning      | Task 7: per-face + averaging quaternions  |
| :---------:                            |        :---------:                           |       :---------:                          |
| xxxxxx            |xxxxxx            |xxxxxx            |


### Task 8.1: context-aware per-vertex LBS
#### Task 8.1.1 visualize the unposed example shapes
| shape name           |  pose 1             |   pose 2            |   pose 3            |
| :------------------: |:------------------: |:------------------: |:------------------: |
| human | <img align="center"  src="./res/placeholder.png" width="300">  | <img align="center"  src="./res/placeholder.png" width="300"> | <img align="center"  src="./res/placeholder.png" width="300"> |

#### Task 8.1.2 skeletal animition using context
| without context   | with context     | 
| :---------:                            |        :---------:                           |  
|<img align="center"  src="./res/placeholder.gif" width="300">  |<img align="center"  src="./res/placeholder.gif" width="300">  |  
