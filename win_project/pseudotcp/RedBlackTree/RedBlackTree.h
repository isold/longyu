//RedBlackTree_.h
#ifndef REDBLACKTREE_H_INCLUDE
#define REDBLACKTREE_H_INCLUDE

#include "RedBlack.h"
#include <assert.h>
#include <string>
#include <iostream>

template<typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::TreeMinIMUM(Node* x )
{
	while(x->left != NIL)
		x = x->left;
	return x;
}
template<typename T>
RedBlackTree<T>::Node*  RedBlackTree<T>::GetNode(void)
{
	return root;
}

template<typename T>
void RedBlackTree<T>::PrintTree(Node* x)
{   
	if(NIL != x){
		if(NIL != x->left)
		{
			PrintTree(x->left);
		}
		if(NIL != x->right)
		{
			PrintTree(x->right);
		}
		std::cout<<x->key<<std::endl;
	}
}

template<typename T>
void RedBlackTree<T>::DeleteTree(Node* x)
{
	if(x != NIL)
	{   
		if(NIL != x->left )
		{
			DeleteTree(x->left);
		}
		if(NIL != x->right  )
		{
			DeleteTree(x->right);
		}
		delete x;
		x = NULL;
	}
}

template<typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::TreeSearchNumber(Node* x, T k)
{
	if( x == NIL || k == x->key )
		return x;
	if( k < x->key )
		return TreeSearchNumber(x->left, k);
	else
		return TreeSearchNumber(x->right, k);
}

template<typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::TreeSuccessor(Node* x)//�����������:
{
	if (x->right != NIL)//������x���������ǿգ���x�ĺ�̼��������е�����Ľ�㡣
		return TreeMinIMUM(x->right) ;
	Node* y = x->parent;//������x��������Ϊ�գ���x��һ�����y����y��x��������Ƚ�㣬
	while( (y != NIL) && (x == x->right))//��y�������Ҳ��x������Ʊƪ p154,p155���㷨���ۡ�
	{
		x = y;
		y = y->parent;
	}
	return y;
}
template<typename T>
void RedBlackTree<T>::LeftRotate(Node* x)
{  
	Node* y  = x->right; //y��x���ҽ��
	if(NIL == y)
		return;
	x->right = y->left;     //��x����ָ��ָ��y�����㡣
	if(NIL != y->left)      //y�����㲻���ڱ�
		y->left->parent = x;//��y�������parentָ��x
	y->parent = x->parent;  //��y�ĸ�����ָ��x�ĸ����
	if(x->parent == NIL) //xΪ�����
	{
		root = y;//��y��Ϊ�����
	}
	else if(x == x->parent->left)//���xΪ����Ů
	{
		x->parent->left = y; //y�����x��Ϊ����Ů
	}
	else
		x->parent->right =y; //�������x��Ϊ����Ů

	y->left = x;            //x��Ϊy������Ů
	x->parent = y;          //y��Ϊx�ĸ����
}
//______________________________________________________________//
//                                                              //
//     |                                 |                      //
//       X      left_Rotate(T,x)           Y                      //
//      /      ----------------->        /                      //
//   ��  Y    <----------------        X  ��                    //
//      /     Right_Rotate(T,y)      /                        //
//       �� ��                         �� ��                      //
//______________________________________________________________//

template<typename T>
void RedBlackTree<T>::RightRotate(Node* y )
{
	Node* x = y->left;
	if(NIL == x)
		return;
	y->left = x->right;
	if(x->right != NIL)
		x->right->parent = y;
	x->parent = y->parent;
	if(y->parent == NIL)
	{
		root = x;
	}
	else if (y == y->parent->right)
	{
		y->parent->right = x;
	}
	else
	{
		y->parent->left = x;
	}

	x->right  = y;
	y->parent = x;
}

template<typename T>
void RedBlackTree<T>::RBInsert(T data)
{     
	Node* x = root;
	Node* z = new Node(data,RED,NULL,NULL,NULL);//��Ҫ����Ľ��
	assert(z != NULL);
	Node* y = NIL;

	while( x != NIL)
	{
		y = x;
		if(z->key < x->key)
		{
			if(x->left != NIL)
			{
				x = x->left;
			}
			else
			{
				break;
			}
		}
		else 
		{    
			if(x->right != NIL)
			{
				x = x->right;
			}
			else
			{
				break;
			}
		}
	}
	z->parent = y;
	if(y == NIL)
		root = z;
	else if(z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = NIL;
	z->right = NIL;
	z->color = RED;
	RBInsertFixup(z);
}

//�ڵ���RBInsertFixup()����Щ����������ʿ��ܻᱻ�ƻ��أ�����1������3��Ȼ����������
//��Ϊ�²���Ľ�����Ů�����ڱ�NIL������5����һ���ƶ���㿪ʼ��ÿ��·���Ϻڽ��ĸ���
//������ȵģ�Ҳ���������Ϊ���z������Ǿ����ڱ���Ů�ĺ��㡣��ˣ����ܱ��ƻ��ľ��Ǹ��ڵ�2��
//�Լ�һ�����㲻���к���Ů������4�����������ܵ��ƻ�����Ϊz����Ϊ��ɫ�����z�Ǹ�������ƻ�������2,
//���z�ĸ�����Ǻ�ɫ���ƻ�������4.

template<typename T>
void RedBlackTree<T>::RBInsertFixup(Node* z)
{    
	Node* y = NIL;
	while( root != z && z->parent->color == RED)
	{
		if( z->parent == z->parent->parent->left)
		{
			y =  z->parent->parent->right;
			if(y != NIL && y->color == RED  )
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else 
			{
				if( z == z->parent->right)
				{
					z = z->parent;
					LeftRotate(z);
				}


				z->parent->color = BLACK;
				z->parent->parent->color = RED;//��û��ת
				RightRotate(z->parent->parent);
			}

		}

		else
		{     
			y =  z->parent->parent->left;
			if(y != NIL && y->color == RED  )
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else 
			{  
				if (z == z->parent->left)
				{
					z = z->parent;
					RightRotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				LeftRotate(z->parent->parent);
			}

		}


	}//while

	root->color = BLACK;

}

template<typename T>
void RedBlackTree<T>::RBDelete(T data)
{     
	Node* x = NIL;
	Node* y = NIL;
	assert(TreeSearchNumber(root, data)->key == data);//���ҿ���û��ֵ��ͬ���ָʾ��һ��
	Node* z = TreeSearchNumber(root, data);//�ҵ��˽��
	if((z->left == NIL) ||(z->right == NIL))
	{
		y = z;
	}
	else
	{
		y = TreeSuccessor(z);
	}
	if(y->left != NIL)
	{
		x = y->left;
	}
	else
	{
		x = y->right;
	}

	x->parent = y->parent;
	if(y->parent == NIL)
		root = x;
	else if(y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	if(y != z)
		z->key = y->key;

	if(y->color == BLACK && NIL != x)
		RBDeleteFixUp(x);

	delete y;
}

template<typename T>
void RedBlackTree<T>::RBDeleteFixUp(Node* x)
{   
	Node* y = NIL;
	Node* w = NIL;
	while(x != root && BLACK == x->color)
	{
		if(x == x->parent->left)
		{
			w = x->parent->right;
			if(NIL == w)
				continue;
			if(w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(x->parent);
				w = x->parent->right;
			}
			if( NIL != w->left &&   BLACK == w->left->color && 
				NIL != w->right && BLACK == w->right->color)
			{
				w->color = RED;
				x = x->parent;
			}
			else 
			{
				if(NIL != w->right && BLACK == w->right->color)
				{
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(w);
					w = x->parent->right;
				}


				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(x->parent);
				x = root;
			}

		}

		else 
		{ 
			w = x->parent->left;
			if(NIL == w)
				continue;
			if(RED == w->color)
			{   
				w->color = BLACK;
				x->parent->color = RED;
				RightRotate(x->parent);
				y = x->parent->left;
			}
			if(NIL != w->left && BLACK == w->left->color &&
				NIL != w->right && BLACK == w->right->color)
			{  
				w->color = RED;
				x = x->parent;
			}
			else 
			{ 
				if(NIL != w->left && w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(w);
					w = x->parent->left;
				}

				w->color = w->parent->color;
				w->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(w->parent);
				x = root;
			}

		}
	}
	x->color = BLACK;
}

#endif