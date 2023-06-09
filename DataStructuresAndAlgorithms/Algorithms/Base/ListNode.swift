//
//  ListNode.swift
//  DataStructuresAnd
//
//  Created by Leo on 2022-12-05.
//
//  链表

public class ListNode {
    public var val: Int
    public var next: ListNode?
	public var random: ListNode?
    
    public init() {
        self.val = 0
        self.next = nil
        self.random = nil
    }
    
    public init(_ val: Int) {
        self.val = val
        self.next = nil
		self.random = nil
    }
    
    public init(
		_ val: Int,
		_ next: ListNode?
	) {
        self.val = val
        self.next = next
		self.random = nil
    }
	
	public init(
		_ val: Int,
		_ next: ListNode?,
		_ random: ListNode?
	) {
		self.val = val
		self.next = next
		self.random = random
	}
}

extension ListNode {
    
    static func getListNode(_ list: [Int]) -> ListNode? {
        
        guard list.count > 0 else {
            return nil
        }
        
        return ListNode(list.first!,
                        getListNode(Array(list.dropFirst())))
    }
    
    static func getResult(_ list: ListNode?,
                          _ sum: [Int] = []) -> [Int] {
        
        guard let list = list else {
            return sum
        }
        
        var arr = sum
        arr.append(list.val)
        
        return getResult(list.next, arr)
    }
}

extension ListNode: Equatable {

	public static func ==(lhs: ListNode, rhs: ListNode) -> Bool {
		return lhs === rhs
	}
}

extension ListNode: Hashable {
	
	public func hash(into hasher: inout Hasher) {
		hasher.combine(val)
		hasher.combine(ObjectIdentifier(self))
	}
}
