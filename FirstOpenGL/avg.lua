-- call a C++ function



MoveTo(1,0,27.9,30,34,1,1,6,15)


MoveToGrouped(1,2,1,31,30.1,34,3,1,2,15)
  

--Parallel Group which is Sequential to each other
MoveToGrouped(1,9,8,29,36,34,1,1,1,10)
MoveToGrouped(9,10,9,30,36,34,1,1,1,10)
MoveToGrouped(10,11,10,31,36,34,1,1,1,10)
MoveToGrouped(11,12,11,32,36,34,1,1,1,10)

--Sequentially Parallel Group with ID=2
MoveToGrouped(2,3,3,35,35,35,2,1,1,15)
MoveToGrouped(2,5,5,20,35,35,2,1,1,15)
MoveToGrouped(2,6,6,20,40,35,2,1,1,15)
MoveToGrouped(2,7,7,35,40,35,2,1,1,15)


MoveToGrouped(7,8,4,35,40,35,2,1,1,15)

OrientToGrouped(2,15,2,0,90,0,5,1,1)

--MoveToGrouped(2,16,2,0,90,0,5,1,1)
