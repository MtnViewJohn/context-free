#region Copyright ©2005, Cristi Potlog - All Rights Reserved
/* ------------------------------------------------------------------- *
*                            Cristi Potlog                             *
*                  Copyright ©2005 - All Rights reserved               *
*                                                                      *
* THIS SOURCE CODE IS PROVIDED "AS IS" WITH NO WARRANTIES OF ANY KIND, *
* EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE        *
* WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR   *
* PURPOSE, NONINFRINGEMENT, OR ARISING FROM A COURSE OF DEALING,       *
* USAGE OR TRADE PRACTICE.                                             *
*                                                                      *
* THIS COPYRIGHT NOTICE MAY NOT BE REMOVED FROM THIS FILE.             *
* ------------------------------------------------------------------- */
#endregion Copyright ©2005, Cristi Potlog - All Rights Reserved

#region References
using System;
using System.Collections;
#endregion

namespace CristiPotlog.Controls
{
	/// <summary>
	/// Represents a collection of wizard pages.
	/// </summary>
	public class WizardPagesCollection : CollectionBase
	{
		#region Fields
		private Wizard owner = null;
		#endregion

		#region Constructor
		/// <summary>
		/// Creates a new instance of the <see cref="WizardPagesCollection"/> class.
		/// </summary>
		/// <param name="owner">A Wizard object that owns the collection.</param>
		internal WizardPagesCollection(Wizard owner)
		{
			this.owner = owner;
		}
		#endregion

		#region Indexer
		public WizardPage this[int index]  
		{
			get  
			{
				return (WizardPage)base.List[index];
			}
			set  
			{
				base.List[index] = value;
			}
		}
		#endregion

		#region Methods
		/// <summary>
		/// Adds an object to the end of the WizardPagesCollection.
		/// </summary>
		/// <param name="value">The WizardPage to be added.
		/// The value can be null.</param>
		/// <returns>An Integer value representing the index at which the value has been added.</returns>
		public int Add(WizardPage value )  
		{		
			int result = List.Add( value );
			return result;
		}

		/// <summary>
		/// Adds the elements of an array of WizardPage objects to the end of the WizardPagesCollection.  
		/// </summary>
		/// <param name="pages">An array on WizardPage objects to be added.
		/// The array itself cannot be null, but it can contain elements that are null.</param>
		public void AddRange(WizardPage[] pages)
		{
			// Use external to validate and add each entry
			foreach(WizardPage page in pages)
			{
				this.Add(page);
			}
		}

		/// <summary>
		/// Searches for the specified WizardPage and returns the zero-based index
		/// of the first occurrence in the entire WizardPagesCollection.
		/// </summary>
		/// <param name="value">A WizardPage object to locate in the WizardPagesCollection.
		/// The value can be null.</param>
		/// <returns></returns>
		public int IndexOf(WizardPage value)
		{
			return List.IndexOf(value);
		}

		/// <summary>
		/// Inserts an element into the WizardPagesCollection at the specified index.
		/// </summary>
		/// <param name="index">An Integer value representing the zero-based index at which value should be inserted.</param>
		/// <param name="value">A WizardPage object to insert. The value can be null.</param>
		public void Insert( int index, WizardPage value )  
		{
			// insert the item
			List.Insert(index, value );
		}

		/// <summary>
		/// Removes the first occurrence of a specific object from the WizardPagesCollection.
		/// </summary>
		/// <param name="value">A WizardPage object to remove. The value can be null.</param>
		public void Remove(WizardPage value)
		{
			// remove the item
			List.Remove(value);
		}

		/// <summary>
		/// Determines whether an element is in the WizardPagesCollection.  
		/// </summary>
		/// <param name="value">The WizardPage object to locate. The value can be null.</param>
		/// <returns>true if item is found in the WizardPagesCollection; otherwise, false.</returns>
		public bool Contains(WizardPage value)  
		{
			return List.Contains(value);
		}

		/// <summary>
		/// Performs additional custom processes after inserting a new element into the WizardPagesCollection instance.
		/// </summary>
		/// <param name="index">The zero-based index at which to insert value.</param>
		/// <param name="value">The new value of the element at index.</param>
		protected override void OnInsertComplete(int index, object value)
		{
			// call base class
			base.OnInsertComplete(index, value);

			// reset current page index
			this.owner.SelectedIndex = index;
		}
	
		/// <summary>
		/// Performs additional custom processes after removing an element from the System.Collections.CollectionBase instance.
		/// </summary>
		/// <param name="index">The zero-based index at which value can be found.</param>
		/// <param name="value">The value of the element to remove from index.</param>
		protected override void OnRemoveComplete(int index, object value)
		{
			// call base class
			base.OnRemoveComplete(index, value);

			// check if removing current page
			if (this.owner.SelectedIndex == index)
			{
				// check if at the end of the list
				if (index < InnerList.Count)
				{
					this.owner.SelectedIndex = index;
				}
				else
				{
					this.owner.SelectedIndex = InnerList.Count - 1;
				}
			}
		}
		#endregion
	}
}
