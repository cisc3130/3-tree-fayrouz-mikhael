// author: levitan

#ifndef NTREE_H
#define NTREE_H

#include <assert.h>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <string.h>
#include <vector>
#include<fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>



namespace std {
	std::string to_string(const std::string& str) { return str; }
}

template <class T>
class NTree {
	struct tnode {
		T data;
		tnode* parent;
		std::vector<tnode*> children;

		tnode (T x) : data(x), parent(NULL) {}

		void addChild(tnode* c) { children.push_back(c); }
	};

	tnode* root;

	// recursive private method called by >> operator
	std::queue<std::string> toStrings(tnode* nd) const {
		std::queue<std::string> rq;
		if (!nd) {	// base case: empty child: return empty vector
			return rq;
		}
		if (nd->children.size()==0) {	// base case: leaf: return vector with just that node's value
			rq.push(std::to_string(nd->data));
			return rq;
		}

		// get queue of strings representing each subtree
		std::vector<std::queue<std::string> > subtrees;
		for (tnode* c : nd->children) {
			subtrees.push_back(toStrings(c));
		}

		// add current value to return queue (will be at front)
		// pad to width of the next level
		int stringWidth = 0;
		int maxDepth = 0;
		for (auto st : subtrees) {
			stringWidth += st.front().length();
			maxDepth = std::max(maxDepth, (int)st.size());
		}
		int levelpad = (stringWidth + subtrees.size() - 1 - std::to_string(nd->data).length())/2;
		rq.push(std::string(levelpad, '_') + std::to_string(nd->data) +
				std::string(levelpad, '_'));

		// add space-padded string(s) to subtrees with fewer levels than max
		for (auto& st : subtrees) {
			int width = st.front().length();
			while (st.size() < maxDepth) {
				st.push(std::string(width, '_'));
			}
		}

		// combine subtrees at each level
		while (!subtrees.front().empty()) {		// all subtrees now have same depth
			std::vector<std::string> levelstrings;	// hold strings at this level
			for (auto& st : subtrees) {
				levelstrings.push_back(st.front());
				st.pop();
			}
			
			// levelstrings now contains string from each subtree
			// combine into single string and add to rq
			std::string levelstr = std::accumulate(levelstrings.begin(),
					levelstrings.end(), std::string(),
					[](const std::string& a, const std::string& b) -> std::string {
							return a + (a.length() > 0 ? " " : "") + b;
					});
			rq.push(levelstr);

		}	// iterate to next level

		// all subtrees have been processed
		return rq;
	}

	std::string toString(tnode* nd) const {
		std::queue<std::string> q = toStrings(nd);
		std::string str;
		while (!q.empty()) {
			str += (q.front() + "\n");
			q.pop();
		}
		return str;
	}

	public:
	NTree() : root(NULL) {}

	NTree(const std::vector<T>& values, const std::vector<int>& parents) {
		if (values.size() != parents.size()) {
			std::cout << "Error: values has " << values.size() << " elements and parents has " << parents.size() << " elements.\n";
			throw std::exception();
		}

		std::map<T, tnode*> valmap;	// will map values to node addresses
		for (int i = 0; i < values.size(); i++) {
			tnode* nd = new tnode(values[i]);
			valmap[values[i]] = nd;
			if (parents[i] >= 0) {		// -1 signals root
				nd->parent = valmap[values[parents[i]]];
				nd->parent->addChild(nd);
			}
			else root = nd;
		}
			
	}

	~NTree() {
		if (!root) return;
		std::queue<tnode*> q;
		q.push(root);
	
		while (!q.empty()) {
			tnode* nd = q.front();
			q.pop();
			for (tnode* c : nd->children) q.push(c);
			delete nd;
		}
	}

	friend std::ostream& operator<<(std::ostream& stream, const NTree& tree) {
		stream << tree.toString(tree.root);
		return stream;
	}

	// TODO: replace dummy return value with test for equality
	bool operator==(const NTree<T>& rhs) {	
		return (help(root, rhs)); // call help function
					
	}
	
	bool help(NTree::tnode*root , const NTree<T>&rhs){ // operator helper
		if((!root)||(!rhs.root))  // chack if there is no root or no rhs.root it returns false
		return false;
			
		if(root->data == rhs.root->data)  // if the both roots have the same data , return true
		return true;
				
		if(root->children.empty()&& rhs.root->children.empty()){ // if the tree have only root with no children 
		if (root->data == rhs.root->data) // if their data are the same return true.
		return true;
	}
		for(int i =0 ; i< (root->children[i] && root->children.size()); i++){ // loop to go over the all of children 
	    if (help((rhs.root->children[i]) , rhs))                               // and do recurion on them
		return true;
	   }
	return false;	
	
}
		
	

	// TODO: implement method to write tree in recoverable format to file
      void serialize(const std::string& filename) {
     	std ::ofstream file;
     	file.open(filename); // opens the file
	
        if (!root)	return; 

        std::queue<tnode*> qu; // create a queue to push the root in it and to store all the children
        qu.push(root); // push the root
  
    
        while(!qu.empty()){
        	
        tnode* rnd = qu.front(); //  rnd is a node which stores the front of the queue  
        qu.pop();
        tnode* pnd = rnd;
        std::stack<tnode*> sta; //  create a stack which holds the parents of the children

        while (pnd !=root){
        sta.push(pnd->parent); // push the parent of the node while it is not equal to the root of the tree
        nd = pnd -> parent;
        }     
        
        while(!sta.empty()){ // while the stack is not empty
 	    file << pnd-> parent ;       	// print the parent to the the file 
 	    std:: cout  << sta.top()->data<< " " ; // gets the top of the stack which will be each parent
 	    sta.pop();
 	    }
	             	 
		std:: cout<< rnd->data << " " <<std::endl; // prints the tree into the file
             
	     for(int i=0 ; i<rnd->children.size() ; i++ ){
                    qu.push(rnd->children[i]); // for loop to push each childern in the queue
            }	 	 

       }
           
		   file.close(); // close the file
		   
        }
         };

	// TODO: implement method to read tree in from file
      void deserialize(const std::string& filename) {
	       	std::string line;
	     	std::ifstream file;
		    file.open(filename);
		
	    	while(file){
	     	std::getline(file,line);
	    	std::string word;
		 
		   std::istringstream ww(word);
		   std::vector<T>vec{std::istream_iterator<std::string>{ww},
		   std::istream_iterator<std::string>{}};
		
	    	tnode* nnd = new tnode(vec.back());// nnd which is the new node that the vector's back
	    	tnode* nd = root;
	    	if(vec.size()==1)
	    	root= nnd; // if the vector is size one this means that it has only one node which is the root
	    	
	    	int i =0;
	    	
	    while(i<vec.size()-1){ // loop over the whole vector to size -1
		int j=0;
	    	while(j < nd->children.size()-1){ // loop over the children size
			if (nd->children[i]->data ==vec[i]){ // find the children that has the value in vector
	    	nd= nd->children[j]; // set nd to that child;
	    	break;	
			}
		   else
			std::cout<<"no tree" << " " <<std::endl; // otherwise prints no tree
			j++;
		  }
		  i++;
	}	  
		nd->addChild(nnd); // nd points to the parent of nnd , so add the child
		nnd -> parent = nd; // then make parent equal to the nd
			}

		file.close();
		
}	
	
};

#endif
