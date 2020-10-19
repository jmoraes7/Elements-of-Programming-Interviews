class Node(object): 

  def __init__(self, d):
    self.data = d
    self.left = None
    self.right = None

  def PrintTree(self):
    if self.left:
      self.left.PrintTree()
    print(self.data)
    if self.right:
      self.right.PrintTree()

def ReconstructAlmostBSTHelper(node, prev):
  if not node: 
    return (None, None)

  (left_min, left_max) = ReconstructAlmostBSTHelper(node.left, node)
  (right_min, right_max) = ReconstructAlmostBSTHelper(node.right, node)

  if (node is prev.left): 
    return 

  if (node is prev.right) and (node.data < prev.data):
    return 

  return (None, None)

def ReconstructAlmostBST(node):
  inversion_0 = (None, None)
  inversion_1 = (None, None)
  

  # (left, left_prev) = ReconstructAlmostBSTHelper(node.left, node)
  # (right, right_prev) = ReconstructAlmostBSTHelper(node.right, node)

  # if left and right: 
  #   return None

  # print(left, right)

def main():
  root = Node(17)

  n1 = Node(41)
  n2 = Node(8)
  n3 = Node(6)

  n4 = Node(23)
  n5 = Node(21)
  n6 = Node(5)
  n7 = Node(30)

  root.left = n1
  root.right = n4

  n1.right = n2
  n2.left = n3

  n4.left = n5
  n4.right = n6

  n6.left = n7

  #root.PrintTree()

  ReconstructAlmostBST(root)

if __name__ == "__main__":
  main()
