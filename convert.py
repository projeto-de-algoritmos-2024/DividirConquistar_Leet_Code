# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def sortedListToBST(self, head: Optional[ListNode]) -> Optional[TreeNode]:
        # transformando a lista encadeada em um array
        arvore = [] 

        # copiando todos os valores de head para a lista
        while head :
            arvore.append(head.value)
            head = head.next
        if arvore == [] :
            return None
        
        # criando a árvore de busca binária balanceada
        def cria_binariaBalanceada(arvore) :
            if arvore == [] or arvore == None :
                return
            elif len(arvore) == 1 :
                return TreeNode[arvore[0]]
            meio = len(arvore)//2
            raiz = TreeNode(arvore[meio])
            raiz.esquerda = cria_binariaBalanceada(arvore[:meio])
            raiz.direita = cria_binariaBalanceada(arvore[meio+1:])
            return raiz
        return cria_binariaBalanceada(arvore)